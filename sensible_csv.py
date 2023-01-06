import pandas as pd
import numpy as np
header = None
df = pd.read_csv('tichana_data.csv', header = header)
pump_status = []
motor_speed = []
heater = []
temp1= []
temp2 = []
humidity1 = []
humidity2 = []

#create a list from the single column data

df.set_axis(['Values'], axis = 'columns', inplace = True)

print(df.head(20))
lst = df['Values'].tolist()

for i, value in enumerate(lst):
    if value == 'ON' or value == 'OFF' and i%2 !=0:
        if value == "ON":
            value = 1
        else:
            value = 0
        pump_status.append(value)
    elif value == 'ON' or value == 'OFF' and i%2 ==0:
        if value == 'ON':
            value =1
        if value == 'OFF':
            value = 0
        heater.append(value)
    elif int(value) >100:
        motor_speed.append(value)
    elif i%3 !=0 and int(value)<40:
        temp1.append(value)
    elif i%3 ==0 and int(value)<40:
        temp2.append(value)
    elif i%2 ==0 and int(value )< 100 and int(value)>40:
        humidity1.append(value)
    elif i%3 !=0 and int(value)<100 and int(value)>40:
        humidity2.append(value)
      
print(len(heater))
print(len(motor_speed))
print(len(temp1))
print(len(pump_status))
df2 = pd.DataFrame({'Temp1': temp1[:195], 'Temp2': temp2[:195], 'Humidity1': humidity1[:195],'Humidity2': humidity2[:195], 'Pump Status':pump_status[:195], 'Heater Status':heater[:195],
                   'Motor Speed': motor_speed[:195]})
print(df2.head(20))

df2.to_csv('clean_sensor_data.csv', index = False)

