**IOT BASED SMART WATER COOLER![](Aspose.Words.5d06e3fb-6708-40ed-9a85-dbd8d6e7d337.001.png)**

**Team Members :**

- Gaurav Bansal (2021101022)
- Ashmit Chamoli (2021101114)
- Jai Bhatnagar (2021111029)
- Siddharth Mangipudi (2021101060)

**Project Idea :**

During hot summers, the need of a water cooler is felt and it is bought in more quantities than an AC, as it is cheaper and consumes less resources. To ease the problems generally faced by people with water coolers kept in rooms, like in our Bakul hostel, our team has decided to work on an IOT based smart water cooler. 

Beginning with the major problems faced, and the technique of tackling them, firstly, the rooms in which water coolers are being used tend to get highly humid due to the presence of excess moisture due to the running of the pump continuously. This problem is usually tackled by switching off the pumps and running of the cooler only on fan. This process would get automated under our project, in which a threshold value set by the user (can be changed anytime), acts as the barrier for switching the pump ON or OFF. The humidity will be measured using a DHT11 module. 

Secondly, another problem seen is the lack of a proper indication of the water level in coolers. Our smart water would come installed with a water level sensor, and have a visual indicator with buzzer sound when the cooler is about to be get full or when its empty. This is required to prevent overflowing while filling using pipes and also safety to the pump. When the water level would fall below a bare minimum threshold, unsafe for the motor/pump, the cooler would stop the pump, increasing it’s longevity. 

Thirdly, the fan of the coolers usually have manually switchable levels, in which we plan to introduce a temperature dependent automatic working as well, which would work on the values of ambient temperature to give best possible functionality. The changing of the levels of the cooler would be governed using a servo-motor to rotate the rotor dials.

We also, would like to ensure that the cooler doesn’t excessively heat up during it’s functioning, after which a rest to it would be provided, again for which an internally installed temperature sensor and a smoke detector sensor would be available. As another safety measure, we would also place a PIR motion sensor between the vents and the fan to check for any human intervention and immediately stop the running cooler if found any, to prevent any accidents, especially during the night time.

Basically, based on the ambient conditions of temperature, humidity and feedback by the user, an optimum and dynamic as well as personalized functioning water cooler would be available, that would work to satisfy all needs automatically. 

All of the above would come with a feedback mechanism via a website, where one can send the satisfaction level with the functioning of the cooler in a particular situation for us to collect data to the cloud platforms and provide a smooth and a more personalized functioning, which can be edited manually, by changing the threshold values, which are dynamically possible to change.

**Required Components :**

- ESP32 Development Board
  - B-10 Buzzer
    - DHT11 Module
- Resistors
  - Breadboards
- Arduino Due Cable
  - LDR Module
    - Jumper wires (m-to-m and m-to-f)
- LEDs
  - Water level sensor
- SG-90 servo motors
  - D830D Digital Multimeter
- HC-SR501 PIR Motion Sensor
  - I2C Module
    - MQ2 smoke detector module

