# Blinds-Controller

Wifi connected blinds with nodeMCU using Blynk

# Circuit Schematic:
![Blinds_Controller_bb](https://user-images.githubusercontent.com/47865653/128824365-9d32a8af-5d22-4667-abc4-2ce7c86c8fdb.png)

(instead of lipo battery and voltage regulator can use 5V PSU)

# Blynk App:
Download Blynk app from Google Play Store or App Store.
Creat new project.
![Screenshot_20210814-154545_Blynk](https://user-images.githubusercontent.com/47865653/129446835-b6ce3e5d-d58e-434a-b432-7f528ec99ba3.jpg)

![Screenshot_20210814-154621_Blynk](https://user-images.githubusercontent.com/47865653/129446841-813f6e29-e9f1-4c36-95bc-dfa2a8c906ce.jpg)
When you created new project you get an email including your Auth Token. Do not forget to write it on code.
Add button and vertical slider.

![Screenshot_20210814-154745_Blynk](https://user-images.githubusercontent.com/47865653/129446851-47b04753-67bb-4276-827c-853208beb014.jpg)

Change button pin as virtual pin V1 and vertical slider pin as virtual pin V2.
Do not forget to change the maximum value of vertical slider same as the turn number in the code.

(Optional) You can add a timer in Blynk so blinds automatically open and close at specified times.

![Screenshot_20210814-155433_Blynk](https://user-images.githubusercontent.com/47865653/129446993-1ebfeea7-2c00-4f76-870d-a484fe03e93b.jpg)


# 3D print parts:
https://www.thingiverse.com/thing:4929543

# Google Assistant connection(Optional):
Open account from the below link and use the same account in your phone.

https://ifttt.com/

Click Create ---> Click if this ---> Search Google Assistant ---> Click Say a simple phrase ---> Fill as you want.(I put ss for example)

![Ekran görüntüsü 2021-08-10 232748](https://user-images.githubusercontent.com/47865653/128930525-1fc0dbbd-e73f-410d-9a2a-d5424fe60942.jpg)

Click Than that ---> Search Webhooks ---> Type to url part https://local_host/aut_token/update/V1 dont forget to change the local host and token. To find local_host opem cmd from your computer and type ping blynk-cloud.com than take the ip adress. 

![Ekran görüntüsü 2021-08-10 234212](https://user-images.githubusercontent.com/47865653/128932164-a2c23cbc-93b7-44a6-9384-033a339e5cbd.jpg)


Type your blynk token to aut_token part.

![Ekran görüntüsü 2021-08-10 233557](https://user-images.githubusercontent.com/47865653/128931433-7e0d063b-6eb0-4ac6-9b2e-527e487a7f29.jpg)

To close the blinds repeat the same steps but change the body part as ["0"]



