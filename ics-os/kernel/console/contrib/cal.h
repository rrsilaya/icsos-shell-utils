/**
 * Calendar module contributed by:
 *   Magnaye, Aaron V.
 *   Silaya, Ralph Lawrence R.
 * as part of the requirements for CMSC 125
 * Second Semester, A.Y. 2017-2018
 */

#define TRUE 1
#define FALSE 0

#define CAL_WIDTH 20
#define WEEK_DAYS 7
#define YEAR_CAL 0

int isLeapYear(int year) {
  /**
   * Algorithm for determining a leap year:
   * http://en.wikipedia.org/wiki/Leap_year
   */
  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
    return TRUE;
  } else return FALSE;
}

int getDaysOfMonth(int month, int year) {
  int days = month % 7 % 2 == 1 ? 31 : 30;

  if (month == 2 /* Month is February */) {
    if (isLeapYear(year)) days = 29;
    else days = 28;
  }

  return days;
}

int getStartDay(int month, int year, int day) {
  /**
   * Algorithm for computing day of Gregorian Calendar:
   * https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
   */
  int startDay;
  int century = (int) year / 100;
  year = month < 3 ? (year - (century * 100)) - 1 : (year - (century * 100)); // rolls if months are jan or feb
  month = month < 3 ? month + 10 : month - 2; // rolls over the month

  startDay = (
    day +
    ((int) (2.6 * month - 0.2)) -
    (2 * century) +
    year +
    ((int) year / 4) +
    ((int) century / 4)
  ) % WEEK_DAYS;

  return startDay < 0 ? WEEK_DAYS + startDay : startDay;
}

void printMonth(int month) {
  char *months[12] = {
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };
  int i, pad = (int) (CAL_WIDTH - strlen(months[month - 1])) / 2;

  // Print left pad
  for (i = 0; i < pad; i++) printf(" ");

  printf("%s", months[month - 1]);

  // Print right pad
  for (i = 0; i < CAL_WIDTH - (pad + strlen(months[month - 1])); i++) printf(" ");
}

void cal_help(){

  printf("NAME\n");
  printf("\tcal - displays a simple, formatted calendar.\n\n");

  printf("SYNTAX\n");
  printf("\tcal\t\ncal [-month] [-year]\t\ncal -h\n\n");

  printf("DESCRIPTION\n");
  printf("The cal utility displays a simple calendar in traditional format. The format is a little cramped but it makes a year fit on a small terminal. If arguments are not specified, the current month is displayed. \n\n");
  printf("The options are as follows: \n");
  printf("\t-h\tDisplays help\n\n");


}

void cal(int month, int year) {
  int startDay, space, currentMonth, dayRow, day[3] = { 1, 1, 1 },
      row, row_limit = month == YEAR_CAL ? 4 : 1,
      col, col_limit = month == YEAR_CAL ? 3 : 1,
      month_offset = month == YEAR_CAL ? 1 : 0;
  char catcher;

  for (row = 0; row < row_limit; row++) {
    day[0] = 1; day[1] = 1; day[2] = 1;

    // Print month labels
    for (col = 0; col < col_limit; col++) {
      printMonth((row * (row_limit - 1)) + col + month + month_offset);
      printf("   ");
    }
    printf("\n");

    // Print day labels
    for (col = 0; col < col_limit; col++) printf("Su Mo Tu We Th Fr Sa   ");
    printf("\n");

    // Print day
    for (dayRow = 0; dayRow < 6; dayRow++) {
      for (col = 0; col < col_limit; col++) {
        currentMonth = (row * (row_limit - 1)) + col + month + month_offset;
        startDay = getStartDay(currentMonth, year, day[col]);

        // Print padded spaces
        for (space = 0; space < startDay; space++) printf("   ");

        // Print days
        for (; (startDay + 1) % 8 != 0; day[col]++, startDay++) {
          if (year == time_systime.year && currentMonth == time_systime.month && day[col] == time_systime.day) {
            textbackground(WHITE);
            textcolor(BLACK);
          }

          if (day[col] < 10) printf(" ");
          if (day[col] <= getDaysOfMonth(currentMonth, year)) {
            printf("%i", day[col]);
            textbackground(BLACK);
            textcolor(WHITE);
            printf(" ");
          }
          else printf("   ");
        }

        printf("  ");
      }

      printf("\n");
    }

    if(row%2 == 1 && row != row_limit - 1){

      printf("Press any key to continue; press q if you want to quit.\n");
      catcher = getch();

      if(catcher == 'q')return;

      clrscr();

    }

    // printf("\n");
  }
}
