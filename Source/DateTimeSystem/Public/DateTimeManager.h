#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "DateTimeManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DateTimeDebug, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinuteUpdated, int32, NewMin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHourUpdated, int32, NewHour);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDayUpdated, FString, NewDay, int32, NewDayNum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeekUpdated, FString, NewWeek);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMonthUpdated, FString, NewMonth, int32, NewMonthNum);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnYearUpdated, int32, NewYear);

USTRUCT(BlueprintType)
struct FCustomMonth
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DaysInMonth;

    // Default constructor (needed for TArray)
    FCustomMonth() : Name(TEXT("")), DaysInMonth(0) {}

    // Custom constructor
    FCustomMonth(FString InName, uint32 InDays)
        : Name(InName), DaysInMonth(InDays) {
    }
};


UCLASS(Blueprintable)
class DATETIMESYSTEM_API ADateTimeManager : public AActor
{
    GENERATED_BODY()

public:
    ADateTimeManager();

    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnMinuteUpdated OnMinuteUpdated;
    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnHourUpdated OnHourUpdated;
    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnDayUpdated OnDayUpdated;
    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnWeekUpdated OnWeekUpdated;
    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnMonthUpdated OnMonthUpdated;
    UPROPERTY(BlueprintAssignable, Category = "DateTime|Bind")
    FOnYearUpdated OnYearUpdated;

    // Use default days/months
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Custom Calendar")
    bool bPrintDebug = false;
    // Use default days/months
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Custom Calendar")
    bool bUseDefaultDateTime = true;
    // Custom days of the week
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Custom Calendar")
    TArray<FString> CustomDaysOfWeek;
    // Custom months of the year
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Custom Calendar")
    TArray<FCustomMonth> CustomMonths;
    // Custom length of days for how long a week is
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Custom Calendar")
    int32 CustomWeekLength;
    // Custom year
    UPROPERTY(BlueprintReadOnly, Category = "DateTime|Custom Calendar")
    int32 CurrentCustomYear = 2025;
    // The index for the current month
    UPROPERTY(BlueprintReadOnly, Category = "DateTime|Custom Calendar")
    int32 CurrentCustomMonthIndex;
    // The index for the current day
    UPROPERTY(BlueprintReadOnly, Category = "DateTime|Custom Calendar")
    int32 CurrentCustomDay;
    // The current custom hour
    UPROPERTY(BlueprintReadOnly, Category = "DateTime|Custom Calendar")
    int32 CurrentCustomHour;
    // The current custom hour
    UPROPERTY(BlueprintReadOnly, Category = "DateTime|Custom Calendar")
    int32 CurrentCustomMinute;
    // How many real life seconds per in-game hour (Default: 60s = 1 hour in-game)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DateTime|Time")
    float RealSecondsPerGameHour = 60; 

    /**
     * @brief StartGameTime
     * 
     * Starts the in-game time progression.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Time")
    void StartGameTime();
    /**
     * @brief StopGameTime
     * 
     * Stops the in-game time progression.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Time")
    void StopGameTime();
    /**
     * @brief AdvanceCustomTime
     * 
     * Advances the custom in-game time by the specified number of days, hours, and minutes.
     * 
     * @param Days The number of days to advance.
     * @param Hours The number of hours to advance.
     * @param Minutes The number of minutes to advance.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Custom Calendar")
    void AdvanceCustomTime(int32 Days, int32 Hours, int32 Minutes);
    /**
     * @brief GetCurrentCustomDayName
     * 
     * Gets the name of the current custom day.
     * 
     * @return The name of the current day in the custom calendar.
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Custom Calendar")
    FString GetCurrentCustomDayName() const;

    /**
     * @brief GetCurrentMonthName
     * 
     * Gets the name of the current custom month.
     * 
     * @return The name of the current month in the custom calendar.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Custom Calendar")
    FString GetCurrentCustomMonthName() const;

    /**
     * @brief GetFormattedCustomTime
     * 
     * Gets the current in-game time formatted as HH:MM.
     * 
     * @return A formatted string representing the current custom time.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "DateTime|Custom Calendar")
    FString GetFormattedCustomTime() const;

protected:
    virtual void BeginPlay() override;
    virtual void BeginDestroy() override;


private:
    void NormalizeCustomDateTime();
    void TickTime(); // Called every timer tick

    FTimerHandle GameTimeTimerHandle;
};
