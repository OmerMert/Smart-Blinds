# Blinds-Controller

Wifi connected blinds with nodeMCU using Blynk

# Circuit Schematic:
![Blinds_Controller_bb](https://user-images.githubusercontent.com/47865653/128824365-9d32a8af-5d22-4667-abc4-2ce7c86c8fdb.png)

(instead of lipo battery and voltage regulator can use 5V PSU)

# Google Assistant connection
Open account from the below link and use the same account in your phone
https://ifttt.com/
Click Create ---> Click if this ---> Search Google Assistant ---> Click Say a simple phrase ---> Fill as you want.(I put ss for example)

![Ekran görüntüsü 2021-08-10 232748](https://user-images.githubusercontent.com/47865653/128930525-1fc0dbbd-e73f-410d-9a2a-d5424fe60942.jpg)

Click Than that ---> Search Webhooks ---> Type to url part https://local_host/aut_token/update/V1 dont forget to change the local host and token. To find local_host opem cmd from your computer and type ping blynk-cloud.com than take the ip adress. type your blynk token to aut_token part.

![Ekran görüntüsü 2021-08-10 233557](https://user-images.githubusercontent.com/47865653/128931433-7e0d063b-6eb0-4ac6-9b2e-527e487a7f29.jpg)

To close the blinds repeat the same steps but change the body part as ["0"]

# 3D print parts:
https://www.thingiverse.com/thing:4929543


