#include <iostream>

#include <string>

/*
  Необходимо определить является ли введенная последовательность символов датой,
  представленной в формате ГГГГ/ МM/ЧЧ.

  Необходимо учитывать високосный год.
  В случае ГГГГ для значений от 0 до 999 используются ведущие нули.
  В случае ММ для значений от 1 до 9 используется ведущий ноль.
  В случае ЧЧ для значений от 1 до 9 используется ведущий ноль.
  В качестве разделителя используется символ «/».
  Примечание: Год является високосным, если его номер кратен 400.
  Или же его номер кратен 4, но не кратен 100.

  Input:
  Последовательность любых символов.
  Output:
  True, если приведенная последовательность символов является датой в формате
  ГГГГ/МM/ЧЧ, иначе False.

  Sample Input:
  2002/10/IV
  Sample Output:
  False
 */

void done(bool res) {
  if (res)
    std::cout << "True";
  else
    std::cout << "False";
  exit(0);
}

int main() {
  std::string input;
  std::getline(std::cin, input);

  if (input.size() != 10)
    done(false);
  if (input[4] != '/' or input[7] != '/')
    done(false);

  char year[5];
  year[0] = input[0];
  year[1] = input[1];
  year[2] = input[2];
  year[3] = input[3];
  year[4] = '\0';
  char month[3];
  month[0] = input[5];
  month[1] = input[6];
  month[2] = '\0';
  char day[3];
  day[0] = input[8];
  day[1] = input[9];
  day[2] = '\0';

  for(int i = 0; i < 4; i ++)
    if (not isdigit(year[i]))
      done(false);
  for(int i = 0; i < 2; i ++)
    if (not isdigit(month[i]))
      done(false);
  for(int i = 0; i < 2; i ++)
    if (not isdigit(day[i]))
      done(false);

  int iYear = atoi(year);
  int iMonth = atoi(month);
  int iDay = atoi(day);

  if (iMonth > 12 or iMonth<= 0)
    done(false);
  if (iDay > 31 or iDay <= 0)
    done(false);

  if (((iMonth == 4) or (iMonth == 6) or (iMonth == 9) or (iMonth == 1)) and
      iDay == 31)
    done(false);

  if (iMonth == 2 and iDay > 29)
    done(false);

  if (((iYear % 400 == 0) or (iYear % 4 == 0 and iYear % 100 == 0))
      and iMonth == 2 and iDay > 28)
    done(false);

  done(true);
  return 0;
}
