# -*- coding: utf-8 -*-
"""
Created on Tue Dec 13 00:50:45 2022

@author: DELL
"""


import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score
import matplotlib.pyplot as plt
import seaborn as sns
import warnings
warnings.filterwarnings("ignore")

company=pd.read_csv("c:\\Users\\DELL\\Documents\\50_Startups.csv")
shape=company.shape
print("Dataset contains {} rows and {} columns".format(shape[0],shape[1]))
company.columns
x=company.iloc[:,:-1].values
y=company.iloc[:,3].values
company.head()

#SPLITTING THE DATASET INTO THE TRAINING SET AND TEST SET

x_train,x_test,y_train,y_test=train_test_split(x,y,test_size=0.2,random_state=0)

#View the shapes of splitter data.
#shapes of splitted data

print("X_train:",x_train.shape)
print("X_test:",x_test.shape)
print("Y_train:",y_train.shape)
print("Y_test:",y_test.shape)

#FITTING LINEAR REGRESSION TO THE TRAINING SET

regressor=LinearRegression()
regressor.fit(x_train,y_train)

print("\nANALYSING: R&D V/S PROFIT")
x1 = company.iloc[:, 0].values
y1 = company.iloc[:, -1].values
plt.scatter(x1,y1,color='Red',s=50)
plt.xlabel('R&D')
plt.ylabel('Profit')
plt.title('R&D vs Profit')
plt.show()

print("\nANALYSING: ADMINISTRATION V/S PROFIT")
x2 = company.iloc[:, 1].values
y2 = company.iloc[:, -1].values
plt.scatter(x2,y2,color='Blue',s=50)
plt.xlabel('Administration')
plt.ylabel('Profit')
plt.title('Administration vs Profit')
plt.show()


print("\nANALYSING: MARKETING SPEND V/S PROFIT")
x3 = company.iloc[:, 2].values
y3 = company.iloc[:, -1].values
plt.scatter(x3,y3,color='Brown',s=50)
plt.xlabel('Marketing Spend')
plt.ylabel('Profit')
plt.title('Marketing Spend vs Profit')
plt.show()



print("\n...................PREDICTING THE PROFIT.................\n\n")

y_pred=regressor.predict(x_test)
print(y_pred)
data = pd.DataFrame(data={"Predicted Profit": y_pred.flatten()})
print(data.head())


print("\n................CALCULATING THE COEFFICIENT....................\n\n")

print(regressor.coef_)

print("\n................CALCULATING THE INTERCEPT.......................\n\n")

print(regressor.intercept_)

print("\n................CALCULATING THE R SQUARED VALUE...................\n\n")

print(r2_score(y_test,y_pred))

print("\n..................PREDICTING THE ACCURACY OF THE MODEL.................\n\n")

Accuracy=r2_score(y_test,y_pred)*100
print(" Accuracy of the model is %.2f" %Accuracy)

print("\n.................PREDICTED VALUE..................\n\n")

pred_df=pd.DataFrame({'Actual Value':y_test,'Predicted Value':y_pred,'Difference':y_test-y_pred})

#View the data frame.
print(pred_df)

print("\n......................FOR DATA VISUALIZATION.....................\n\n")


print("1. For scatter plot between actual values and predicted values\n")
print("2. Regression plot of our model\n")
print("3.  Heatmap\n")

plt.scatter(y_test,y_pred)
plt.xlabel('Actual')
plt.ylabel('Predicted')
plt.show()

sns.regplot(x=y_test,y=y_pred,ci=None,color ='Green')

#sns.heatmap(company.corr())

   
    
    






































