import sklearn as sk
from sklearn.model_selection import train_test_split
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sb


df = pd.read_csv('clean_sensor_data.csv')
#using IDLE which does not return the output of a shell, hence the print statement
print(df.head())
print(df.describe())
print(df.info())
print(df.dtypes)

#plot general relationships (scatter) between inputs and output, motor speed
X = df.iloc[:, 1:-1].values 
y = df.iloc[:, -1].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)

from sklearn.linear_model import LinearRegression

regr = LinearRegression()
model=regr.fit(X_train, y_train)
#print(model.coef_)
#test1
#X_train.shape
print(X_train[:1])  #show row zero
print("y value=", y_train[:1])  #what is its corresponding Y value
print ("value predicted by model= ",regr.predict(   X_train[:1]  )) #apply row 0 to model and see what is predicted
from sklearn.metrics import mean_absolute_error as mae
# Evaluate our model using MAE criterion
y_pred = regr.predict(X_test)
maae=mae(y_test, y_pred)
print("Mean Average Error (MAE): ", maae)
