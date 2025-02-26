#include "DateTimeManager.h"
#include "Engine/World.h"
#include "TimerManager.h"

ADateTimeManager::ADateTimeManager()
{

}

// Start the game time loop
void ADateTimeManager::StartGameTime()
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(GameTimeTimerHandle, this, &ADateTimeManager::TickTime, RealSecondsPerGameHour / 60.0f, true);
    }
}

// Stop the game time loop
void ADateTimeManager::StopGameTime()
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(GameTimeTimerHandle);
    }
}

// Called every second (advances by 1 in-game minute)
void ADateTimeManager::TickTime()
{
    AdvanceCustomTime(0, 0, 1);
}

// Advances the Custom Time
void ADateTimeManager::AdvanceCustomTime(int32 Days, int32 Hours, int32 Minutes)
{
    CurrentCustomMinute += Minutes;
    CurrentCustomHour += Hours;
    CurrentCustomDay += Days;

    NormalizeCustomDateTime();
}

// Normalizes time so that minutes/hours/days wrap properly
void ADateTimeManager::NormalizeCustomDateTime()
{
    // Normalize Minutes
    while (CurrentCustomMinute >= 60)
    {
        CurrentCustomMinute -= 60;
        CurrentCustomHour++;
    }

    // Normalize Hours
    while (CurrentCustomHour >= 24)
    {
        CurrentCustomHour -= 24;
        CurrentCustomDay++;
    }

    // Normalize Days
    while (CurrentCustomDay > CustomMonths[CurrentCustomMonthIndex].DaysInMonth)
    {
        CurrentCustomDay -= CustomMonths[CurrentCustomMonthIndex].DaysInMonth;
        CurrentCustomMonthIndex++;

        if (CurrentCustomMonthIndex >= CustomMonths.Num()) // New Year
        {
            CurrentCustomMonthIndex = 0;
            CurrentCustomYear++;
        }
    }
}

// Gets the current day's name from the custom calendar
FString ADateTimeManager::GetCurrentCustomDayName() const
{
    if (CustomDaysOfWeek.Num() == 0) return TEXT("Invalid Day");

    int32 DayIndex = (CurrentCustomDay - 1) % CustomWeekLength;
    return CustomDaysOfWeek.IsValidIndex(DayIndex) ? CustomDaysOfWeek[DayIndex] : TEXT("Unknown");
}

// Gets the current month's name from the custom calendar
FString ADateTimeManager::GetCurrentMonthName() const
{
    return CustomMonths.IsValidIndex(CurrentCustomMonthIndex) ? CustomMonths[CurrentCustomMonthIndex].Name : TEXT("Unknown");
}

FString ADateTimeManager::GetFormattedCustomTime() const
{
    return FString::Printf(TEXT("%02d:%02d"), CurrentCustomHour, CurrentCustomMinute);
}

void ADateTimeManager::BeginPlay()
{
    if (bUseDefaultDateTime)
    {
        // Clean old data
        CustomDaysOfWeek.Empty();
        CustomMonths.Empty();

        // Default Custom Calendar Setup
        CustomDaysOfWeek = { TEXT("Sun"), TEXT("Mon"), TEXT("Tue"), TEXT("Wed"), TEXT("Thu"), TEXT("Fri"), TEXT("Sat") };
        CustomWeekLength = 7;

        CustomMonths.Add(FCustomMonth(TEXT("January"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("February"), 28));
        CustomMonths.Add(FCustomMonth(TEXT("March"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("April"), 30));
        CustomMonths.Add(FCustomMonth(TEXT("May"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("June"), 30));
        CustomMonths.Add(FCustomMonth(TEXT("July"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("August"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("September"), 30));
        CustomMonths.Add(FCustomMonth(TEXT("October"), 31));
        CustomMonths.Add(FCustomMonth(TEXT("November"), 30));
        CustomMonths.Add(FCustomMonth(TEXT("December"), 31));


        CurrentCustomMonthIndex = 0;
        CurrentCustomDay = 1;
        CurrentCustomHour = 12;
        CurrentCustomMinute = 0;
    }

    Super::BeginPlay();
}


// Cleanup
void ADateTimeManager::BeginDestroy()
{
    StopGameTime();
    Super::BeginDestroy();
}
