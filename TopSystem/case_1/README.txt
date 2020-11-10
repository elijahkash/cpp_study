Задача с хакатона SafeBoard от Лаборатории Касперского (октябрь 2020).

Описание:
Недавно был написан код, активно использующий исключения для обработки ошибок.
В частности, использовался механизм std::nested_exception, чтобы исключения можно было объединять в "цепочку";
затем, в финальном блоке catch() выводить в лог всю последовательность событий, приведших к ошибке - это
сильно упрощает диагностику проблем.

Нам дали небольшой кусочек (приведен ниже) и попросили переписать его без использования исключений, сохранив логику.
Сообщения об ошибках должны выглядеть так же, как в исходном коде.
Все функции должны быть объявлены noexcept, использовать конструкции try/catch запрещается.


Для решение данной задачи, я разработал шаблон WrapError (см. './wrap_error.hpp' ).
Исправленный код использующий данный шаблон можно найти в './example.cpp'
Файл './test.cpp' содержит unit-тесты для проверки работоспособности
 - для unit-тестирования используется фреймворк 'Catch2'
 - для компиляции используется CMake
Код оформлен в соответствии с Google C++ Style Guide



Исходный код:

#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;
struct Requester
{
    string name;
    uint64_t ownerId;
};

struct RequestFromConfig
{
    string name;
    string requester;
    string type;
};

enum class RequestType
{
    Drop, Apply, Validate
};

struct Request
{
    RequestType type;
    uint64_t ownerId;
};

RequestType GetRequestType(const RequestFromConfig& request)
{
    if (request.type == "drop")
        return RequestType::Drop;
    if (request.type == "apply")
        return RequestType::Apply;
    if (request.type == "validate")
        return RequestType::Validate;
    throw runtime_error(string("unknown type '") + request.type + "'");
}

Request BuildRequest(const vector<Requester>& availableRequesters, const RequestFromConfig& requestFromConfig)
{

    Request request;
    auto it = find_if(begin(availableRequesters), end(availableRequesters), [&](const Requester& requester)
        {return requester.name == requestFromConfig.requester; });
    if (it == end(availableRequesters))
        throw runtime_error(string("unknown requester '") + requestFromConfig.requester + "'");
    request.type = GetRequestType(requestFromConfig);
    request.ownerId = it->ownerId;
    return request;

}
struct Queue
{
    uint32_t id;
    vector<Request> requests;
};
Queue BuildRequestQueue(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests)
{
    static uint32_t nextId = 0;
    nextId++;
    try
    {
        Queue result;
        result.id = nextId;
        for (const auto& requestFromConfig : requests)
            result.requests.push_back(BuildRequest(availableRequesters, requestFromConfig));
        return result;
    }

    catch (...)
    {
        ostringstream message("");
        message << "can't build request queue #" << nextId;
        std::throw_with_nested(std::runtime_error(message.str()));
    }
}

void print_exception(const std::exception& e, int level = 0)
{
    cout << string(level, ' ') << (level ? "because: " : "high-level operation failed: ") << e.what() << '\n';
    try
    {
        std::rethrow_if_nested(e);
    }
    catch (const std::exception& e)
    {
        print_exception(e, level + 1);
    }
    catch (...) {}
}
void PrintTaskResult(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests)
{
    try
    {
        auto queue = BuildRequestQueue(availableRequesters, requests);
        for (const auto& request : queue.requests)
            cout << "request in queue #" << queue.id << ": " << static_cast<int>(request.type) << " / " << request.ownerId << endl;
    }
    catch (const std::exception& ex)
    {
        print_exception(ex);
    }
    cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////

int main() // examples
{
    PrintTaskResult(
        { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
        { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
    /* [output]

    request in queue #1: 0 / 2
    request in queue #1: 1 / 2
    request in queue #1: 1 / 1

    */
    PrintTaskResult(
        { { "second_requester", 2 }, { "third_requester", 3 } },
        { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
    /* [output]

    high-level operation failed: can't build request queue #2
     because: unknown requester 'first_requester'
    */

    PrintTaskResult(
        { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
        { { "Johny", "third_requester", "drop" }, { "Sam", "third_requester", "apply" }, { "Louise", "first_requester", "apply" } });

    /* [output]
    request in queue #3: 0 / 3
    request in queue #3: 1 / 3
    request in queue #3: 1 / 1
    */

    PrintTaskResult(
        { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
        { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "reapply" } });
    /* [output]
    high-level operation failed: can't build request queue #4
     because: unknown type 'reapply'
    */
    return 0;
}
