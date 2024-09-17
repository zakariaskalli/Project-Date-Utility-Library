#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class clsDate
{
private:

	int _Day = 1;  
	int _Month = 1;
	int _Year = 1900;

	vector <string> _SplitString(string S1, string delim)
	{
		vector <string> vString;

		short pos = 0;
		string sWorld;


		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWorld = S1.substr(0, pos);

			if (sWorld != "")
				vString.push_back(sWorld);

			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
			vString.push_back(S1);

		return vString;
	}

	clsDate _StringToDate(string DateString)
	{
		clsDate Date;
		vector <string> vDate;

		vDate = _SplitString(DateString, "/");
		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);


		return Date;
	}

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;

	}

	clsDate(string DateString)
	{
		clsDate Date;

		Date = _StringToDate(DateString);

		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}

	clsDate(int Day, int Month, int Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(int DateOrderInYear, int Year)
	{
		GetDataFromDayOrderInYear(DateOrderInYear, Year, *this);
	}


	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;


	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;


	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;


	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}


	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date._Year = now->tm_year + 1900;
		Date._Month = now->tm_mon + 1;
		Date._Day = now->tm_mday;

		return Date;
	}


	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}


	static short NumberOfDaysInAYear(short Year)
	{
		return (IsLeapYear(Year)) ? 366 : 365;

	}

	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}


	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}


	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}


	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}


	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 0 || Month > 12)
			return 0;

		if (Month == 2)
			return IsLeapYear(Year) ? 29 : 28;

		short Arr31Month[7] = { 1,3,5,7,8,10,12 };

		for (short i = 1; i <= 7; i++)
		{
			if (Arr31Month[i - 1] == Month)
				return 31;
		}

		return 30;
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}


	static short NumberOfHoursInAMonth(short Month, short Year)
	{
		return NumberOfDaysInAMonth(Month, Year) * 24;
	}

	short NumberOfHoursInAMonth()
	{
		return NumberOfHoursInAMonth(_Month, _Year);
	}


	static int NumberOfMinutesInAMonth(short Month, short Year)
	{
		return NumberOfHoursInAMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInAMonth()
	{
		return NumberOfMinutesInAMonth(_Month, _Year);
	}


	static int NumberOfSecondsInAMonth(short Month, short Year)
	{
		return NumberOfMinutesInAMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInAMonth()
	{
		return NumberOfSecondsInAMonth(_Month, _Year);
	}

	
	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}


	static string DayShortName(short DayOfWeekOrder)
	{
		string NameDayOfWeek[] = { "Sun", "Mon", "Tue", "Wed" , "Thu", "Fri", "Sat" };

		return NameDayOfWeek[DayOfWeekOrder];
	}

	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}

	
	static string MonthShortName(short MonthOfYearOrder)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
									"Apr" , "May", "Jun",
									"Jul", "Aug", "Sep",
									"Oct", "Nov", "Dec" };

		return Months[MonthOfYearOrder - 1];
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	
	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;

		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInAMonth(Month, Year);


		printf("\n  ________________%s________________\n\n",
			MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;
		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				cout << "\n";
			}
		}

		printf("\n  ___________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}


	static void PrintYearCalendar(short Year)
	{
		printf("\n  ___________________________________\n\n");
		printf("           Calendar - %d\n", Year);
		printf("\n  ___________________________________\n");

		for (int i = 1; i <= 12; i++)
			PrintMonthCalendar(i, Year);
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}


	static short NumberOfDaysFromTheBeginningOfTheYear(short Year, short Month, short Day)
	{
		short TotalDay = 0;

		for (int i = 1; i <= Month - 1; i++)
		{
			TotalDay += NumberOfDaysInAMonth(i, Year);
		}

		TotalDay += Day;

		return TotalDay;
	}

	short NumberOfDaysFromTheBeginningOfTheYear()
	{
		return NumberOfDaysFromTheBeginningOfTheYear(_Year, _Month, _Day);
	}


	static clsDate GetDataFromDayOrderInYear(short DateOrderInYear, short Year, clsDate & Date)
	{
		short RemainingNumber = DateOrderInYear;
		short MonthDays = 0;

		Date._Year = Year;
		Date._Month = 1;


		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

			if (RemainingNumber > MonthDays)
			{
				RemainingNumber -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingNumber;
				break;
			}
		}

		return Date;
	}

	clsDate GetDataFromDayOrderInYear(short DateOrderInYear)
	{
		return GetDataFromDayOrderInYear(DateOrderInYear, _Year, *this);
	}


	static clsDate DateAddDays(short AddDays, clsDate Date)
	{

		int RemainingNumber = AddDays + NumberOfDaysFromTheBeginningOfTheYear(Date._Year, Date._Month, Date._Day);
		short MonthDays = 0;

		Date._Month = 1;


		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

			if (RemainingNumber > MonthDays)
			{
				RemainingNumber -= MonthDays;
				Date._Month++;

				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}
			else
			{
				Date._Day = RemainingNumber;
				break;
			}
		}

		return Date;

	}

	clsDate DateAddDays(short AddDays)
	{
		clsDate Date;

		Date = DateAddDays(AddDays, *this);

		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;

		return Date;
	}


	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year ==
			Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month ==
				Date2._Month ? Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}


	static bool IsDate1EqualDate1(clsDate Date1, clsDate Date2)
	{

		return (Date1._Year == Date2._Year) ? (Date1._Month == Date2._Month ? (Date1._Day == Date2._Day ? true : false) : false) : false;
	}

	bool IsDate1EqualDate1(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}


	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}


	static bool IsLastMonthInYear(short Month)
	{
		return (12 == Month);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}


	static clsDate IncreaseDateByOneDay(clsDate & Date)
	{

		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else
			{
				Date._Month++;
				Date._Day = 1;
			}
		}
		else
			Date._Day += 1;

		return Date;
	}

	clsDate IncreaseDateByOneDay()
	{
		return IncreaseDateByOneDay(*this);
	}


	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temporary;

		Temporary._Year = Date1._Year;
		Temporary._Month = Date1._Month;
		Temporary._Day = Date1._Day;

		Date1._Year = Date2._Year;
		Date1._Month = Date2._Month;
		Date1._Day = Date2._Day;
			  
		Date2._Year = Temporary._Year;
		Date2._Month = Temporary._Month;
		Date2._Day = Temporary._Day;

	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}


	static clsDate IncreaseDateByXDays(clsDate & Date, short NumberDaysAdd)
	{

		for (short i = 0; i < NumberDaysAdd; i++)
			Date = IncreaseDateByOneDay(Date);

		return Date;
	}

	clsDate IncreaseDateByXDays(short NumberDaysAdd)
	{
		return IncreaseDateByXDays(*this, NumberDaysAdd);
	}


	static clsDate IncreaseDateByOneWeek(clsDate & Date)
	{

		for (short i = 0; i < 7; i++)
			Date = IncreaseDateByOneDay(Date);

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}


	static clsDate IncreaseDateByXWeeks(clsDate & Date, short NumberWeeksAdd)
	{

		for (short i = 0; i < NumberWeeksAdd; i++)
			Date = IncreaseDateByOneWeek(Date);

		return Date;
	}

	void IncreaseDateByXWeeks(short NumberWeeksAdd)
	{
		IncreaseDateByXWeeks(*this, NumberWeeksAdd);
	}


	static clsDate IncreaseDateByOneMonth(clsDate & Date)
	{

		if (IsLastMonthInYear(Date._Month))
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}


	static clsDate IncreaseDateByXMonths(clsDate & Date, short NumberMonthsAdd)
	{

		for (short i = 0; i < NumberMonthsAdd; i++)
			Date = IncreaseDateByOneMonth(Date);

		return Date;
	}

	void IncreaseDateByXMonths(short NumberMonthsAdd)
	{
		IncreaseDateByXMonths(*this, NumberMonthsAdd);
	}


	static clsDate IncreaseDateByOneYear(clsDate & Date)
	{
		Date._Year++;

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}


	static clsDate IncreaseDateByXYears(clsDate & Date, short NumberYearsAdd)
	{

		for (short i = 0; i < NumberYearsAdd; i++)
			Date = IncreaseDateByOneYear(Date);

		return Date;
	}

	void IncreaseDateByXYears(short NumberYearsAdd)
	{
		IncreaseDateByXYears(*this, NumberYearsAdd);
	}


	static clsDate IncreaseDateByXYearsFaster(clsDate & Date, short NumberYearsAdd)
	{
		Date._Year += NumberYearsAdd;

		return Date;
	}

	void IncreaseDateByXYearsFaster(short NumberYearsAdd)
	{
		IncreaseDateByXYearsFaster(*this, NumberYearsAdd);
	}


	static clsDate IncreaseDateByOneDecade(clsDate & Date)
	{
		Date._Year += 10;

		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}


	static clsDate IncreaseDateByXDecades(clsDate & Date, short NumberDecadesAdd)
	{

		for (short i = 0; i < NumberDecadesAdd * 10; i++)
			Date = IncreaseDateByOneYear(Date);

		return Date;
	}

	void IncreaseDateByXDecades(short NumberDecadesAdd)
	{
		IncreaseDateByXDecades(*this, NumberDecadesAdd);
	}


	static clsDate IncreaseDateByXDecadesFaster(clsDate & Date, short NumberDecadesAdd)
	{
		Date._Year += NumberDecadesAdd * 10;

		return Date;
	}

	void IncreaseDateByXDecadesFaster(short NumberDecadesAdd)
	{
		IncreaseDateByXDecadesFaster(*this, NumberDecadesAdd);
	}


	static clsDate IncreaseDateByOneCountry(clsDate & Date)
	{
		Date._Year += 100;

		return Date;
	}

	void IncreaseDateByOneCountry()
	{
		IncreaseDateByOneCountry(*this);
	}


	static clsDate IncreaseDateByOneMillennium(clsDate & Date)
	{
		Date._Year += 1000;

		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}


	static clsDate DecreaseDateByOneDay(clsDate & Date)
	{

		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{		 
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}		 
			else	 
			{		 
				Date._Month--;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}
		}
		else
			Date._Day--;

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}


	static clsDate DecreaseDateByXDays(clsDate & Date, short NumberDaysSub)
	{

		for (short i = 0; i < NumberDaysSub; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}

	void DecreaseDateByXDays(short NumberDaysSub)
	{
		DecreaseDateByXDays(*this, NumberDaysSub);
	}


	static clsDate DecreaseDateByOneWeek(clsDate & Date)
	{

		for (short i = 0; i < 7; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}


	static clsDate DecreaseDateByXWeeks(clsDate & Date, short NumberWeeksSub)
	{
		for (short i = 0; i < NumberWeeksSub; i++)
			Date = DecreaseDateByOneWeek(Date);

		return Date;
	}

	void DecreaseDateByXWeeks(short NumberWeeksSub)
	{
		DecreaseDateByXWeeks(*this, NumberWeeksSub);
	}


	static clsDate DecreaseDateByOneMonth(clsDate & Date)
	{

		if (Date._Month == 1)
		{		 
			Date._Month = 12;
			Date._Year--;
		}		 
		else
			Date._Month--;

		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}


	static clsDate DecreaseDateByXMonths(clsDate & Date, short NumberMonthsSub)
	{

		for (short i = 0; i < NumberMonthsSub; i++)
			Date = DecreaseDateByOneMonth(Date);

		return Date;
	}

	void DecreaseDateByXMonths(short NumberMonthsSub)
	{
		DecreaseDateByXMonths(*this, NumberMonthsSub);
	}


	static clsDate DecreaseDateByOneYear(clsDate & Date)
	{
		Date._Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}


	static clsDate DecreaseDateByXYears(clsDate & Date, short NumberYearsSub)
	{

		for (short i = 0; i < NumberYearsSub; i++)
			Date = DecreaseDateByOneYear(Date);

		return Date;
	}

	void DecreaseDateByXYears(short NumberYearsSub)
	{
		DecreaseDateByXYears(*this, NumberYearsSub);
	}


	static clsDate DecreaseDateByXYearsFaster(clsDate & Date, short NumberYearsSub)
	{
		Date._Year -= NumberYearsSub;

		return Date;
	}

	void DecreaseDateByXYearsFaster(short NumberYearsSub)
	{
		DecreaseDateByXYearsFaster(*this, NumberYearsSub);
	}

	
	static clsDate DecreaseDateByOneDecade(clsDate & Date)
	{
		Date._Year -= 10;

		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}


	static clsDate DecreaseDateByXDecades(clsDate & Date, short NumberDecadesSub)
	{

		for (short i = 0; i < NumberDecadesSub * 10; i++)
			Date = DecreaseDateByOneYear(Date);

		return Date;
	}

	void DecreaseDateByXDecades(short NumberDecadesSub)
	{
		DecreaseDateByXDecades(*this, NumberDecadesSub);
	}


	static clsDate DecreaseDateByXDecadesFaster(clsDate & Date, short NumberDecadesSub)
	{
		Date._Year -= NumberDecadesSub * 10;

		return Date;
	}

	void DecreaseDateByXDecadesFaster(short NumberDecadesSub)
	{
		DecreaseDateByXDecadesFaster(*this, NumberDecadesSub);
	}


	static clsDate DecreaseDateByOneCentury(clsDate & Date)
	{
		Date._Year -= 100;

		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}


	static clsDate DecreaseDateByOneMillennium(clsDate & Date)
	{
		Date._Year -= 1000;

		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}


	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date) == 0;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}


	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}


	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}


	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}


	static short DaysUntilTheEndOfMonth(clsDate Date1)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate._Day = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
		EndOfMonthDate._Month = Date1._Month;
		EndOfMonthDate._Year = Date1._Year;


		return GetDifferenceInDays(Date1, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}


	static short DaysUntilTheEndOfYear(clsDate Date1)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate._Day = 31;
		EndOfMonthDate._Month = 23;
		EndOfMonthDate._Year = Date1._Year;

		return GetDifferenceInDays(Date1, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}


	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DaysCount;
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}


	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (int i = 1; i <= VacationDays + WeekEndCounter; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	clsDate CalculateVacationReturnDate(short VacationDays)
	{
		return CalculateVacationReturnDate(*this, VacationDays);
	}


	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate1(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}


	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDate(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate1(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	enDateCompare CompareDate(clsDate Date2)
	{
		return CompareDate(*this, Date2);
	}


	static bool IsValidateDate(clsDate Date)
	{
		if (Date._Day < 1 || Date._Day > 31)
			return false;

		if (Date._Month < 1 || Date._Month > 12)
			return false;

		if (Date._Month == 2)
		{
			if (IsLeapYear(Date._Year))
			{
				if (Date._Day > 29)
					return false;
			}
			else
			{
				if (Date._Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > DaysInMonth)
			return false;

		return true;
	}

	bool IsValid()
	{
		return IsValidateDate(*this);
	}


	static string ReplaceWordInString(string S1, string StringToReplace, string sReplaceTo)
	{
		short pos = S1.find(StringToReplace);

		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
			pos = S1.find(StringToReplace);
		}

		return S1;
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormatTodDateString = "";

		FormatTodDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date._Day));
		FormatTodDateString = ReplaceWordInString(FormatTodDateString, "mm", to_string(Date._Month));
		FormatTodDateString = ReplaceWordInString(FormatTodDateString, "yyyy", to_string(Date._Year));

		return FormatTodDateString;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}
	

	static int CalculateMyAgeInDays(clsDate Date2)
	{
		clsDate Date1 = GetSystemDate();

		return GetDifferenceInDays(Date2, Date1);
	}

};

