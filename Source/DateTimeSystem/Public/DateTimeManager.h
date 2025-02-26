#pragma once

#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "DateTimeManager.generated.h"

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
    FCustomMonth(FString InName, int32 InDays)
        : Name(InName), DaysInMonth(InDays) {
    }
};


UCLASS(Blueprintable)
class DATETIMESYSTEM_API ADateTimeManager : public AActor
{
    GENERATED_BODY()

public:
    ADateTimeManager();

    virtual void BeginDestroy() override;

    // Use default days/months
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Calendar")
    bool bUseDefaultDateTime = true;
    // Custom days of the week
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Calendar")
    TArray<FString> CustomDaysOfWeek;
    // Custom months of the year
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Calendar")
    TArray<FCustomMonth> CustomMonths;
    // Custom length of days for how long a week is
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Calendar")
    int32 CustomWeekLength;
    // Custom year
    UPROPERTY(BlueprintReadOnly, Category = "Custom Calendar")
    int32 CurrentCustomYear = 2025;
    // The index for the current month
    UPROPERTY(BlueprintReadOnly, Category = "Custom Calendar")
    int32 CurrentCustomMonthIndex;
    // The index for the current day
    UPROPERTY(BlueprintReadOnly, Category = "Custom Calendar")
    int32 CurrentCustomDay;
    // The current custom hour
    UPROPERTY(BlueprintReadOnly, Category = "Custom Calendar")
    int32 CurrentCustomHour;
    // The current custom hour
    UPROPERTY(BlueprintReadOnly, Category = "Custom Calendar")
    int32 CurrentCustomMinute;
    // How many real life seconds per in-game hour (Default: 60s = 1 hour in-game)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Control")
    float RealSecondsPerGameHour = 60; 

    /**
     * @brief StartGameTime
     * 
     * Starts the in-game time progression.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "Time")
    void StartGameTime();
    /**
     * @brief StopGameTime
     * 
     * Stops the in-game time progression.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "Time")
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
    UFUNCTION(BlueprintCallable, Category = "Custom Calendar")
    void AdvanceCustomTime(int32 Days, int32 Hours, int32 Minutes);
    /**
     * @brief GetCurrentCustomDayName
     * 
     * Gets the name of the current custom day.
     * 
     * @return The name of the current day in the custom calendar.
     */
    UFUNCTION(BlueprintCallable, Category = "Custom Calendar")
    FString GetCurrentCustomDayName() const;

    /**
     * @brief GetCurrentMonthName
     * 
     * Gets the name of the current custom month.
     * 
     * @return The name of the current month in the custom calendar.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "Custom Calendar")
    FString GetCurrentMonthName() const;

    /**
     * @brief GetFormattedCustomTime
     * 
     * Gets the current in-game time formatted as HH:MM.
     * 
     * @return A formatted string representing the current custom time.
     * 
     */
    UFUNCTION(BlueprintCallable, Category = "Custom Calendar")
    FString GetFormattedCustomTime() const;

protected:
    virtual void BeginPlay() override;


private:
    void NormalizeCustomDateTime();
    void TickTime(); // Called every timer tick

    FTimerHandle GameTimeTimerHandle;
};
