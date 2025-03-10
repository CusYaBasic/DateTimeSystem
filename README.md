# Unreal Engine 5 Custom Date and Time System:
 This is a Date and Time System for Unreal Engine 5; It handles Dates and Time in standard or your own custom format.

### Pros:
* Pretty much plug and play; All logic is ran from a single actor ```DateTimeManager```
* Use standard DateTime or create your own, days, months and week lengths
* Easy to use; Straight-forward with no bloat
* Blueprint accessable; No code required
* Uses timers; Not tick
* Clean and commented

### Cons:
* Not network replicated
---

## Getting Started:
1. First thing you need to do is add the ```DateTimeManager``` actor to your world

![image](https://github.com/user-attachments/assets/05dc8f0f-70aa-4d45-b4e5-6cb5c0f3bf2a)

2. Once the actor has been added; tweak the settings to your liking  

![image](https://github.com/user-attachments/assets/00145383-d9c1-45c1-a625-35997009e75a)

and thats it! You're now all set and can start using the Date and Time plugin!

---

## Using the Plugin:
Using the plugin is very simple; all you need to do is call ```StartGameTime()``` and it will start counting time (if you have ```bStartOnBeginPlay``` set as ```true``` you can skip this).  

![image](https://github.com/user-attachments/assets/744dc970-5914-4235-9024-115d6a1b891c)

Stopping time is just as easy; Just call ```StopGameTime()```.

![image](https://github.com/user-attachments/assets/6f5f6e04-a8a1-4a2c-a5d4-4777fde29efb)

We can directly change time without any delegates firing by using ```SetGameTime()```

![image](https://github.com/user-attachments/assets/0bb12270-bed3-462c-a911-8f7e212cabcd)

If you have ```bUseDefaultDateTime``` set to ```true```, then the actor we clear all data and replace it with the standard DateTime (Don't use this is we want custom days/months etc)

![image](https://github.com/user-attachments/assets/fab17a59-baec-46a3-9e40-99dafdaf4db1)

### Delegates:
There are a few ```Delegates``` that you can bind too when time advances.  

![image](https://github.com/user-attachments/assets/ffb2dee5-2c2b-4372-9305-bc0c240a9668)

---
## Tutorial Video

COMING SOON TO A HOOD NEAR YOU!

---

## License
This plugin is licensed under **CC BY-NC 4.0**.  
You can use it for free in commercial and personal projects, but **you cannot sell or distribute** this plugin or any modified version of it.  
See the full license: [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/)

---
