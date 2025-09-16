#!/usr/bin/env python
# coding: utf-8

# CONCRETE COMPRESSIVE STRENGTH MODEL PREDICTOR AND PROCESS

# MODEL BUILDING PROCESS:

# In[ ]:


# In order to build model, Split the dataset into features (X) and target (y).
#Standardize the features since linear regression is sensitive to the scale of input data.
#Split the data into training and testing sets.
#Train a linear regression model on the training set.


# ASSESSING DATA MODEL QUALITY:

# In[ ]:


# must evaluate model using the testing set.
# Use metrics such as R-squared, 
#Mean Absolute Error (MAE), and Root Mean Squared Error (RMSE) to assess the quality and accuracy of the model


# BUILDING USER INPUT MODEL

# In[5]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
import numpy as np
import pandas as pd
# Load the data
concrete_data = pd.read_csv('Concrete_Data2.csv')

# Split the data into features and target
X = concrete_data.drop('Concrete compressive strength(MPa, megapascals) ', axis=1)
y = concrete_data['Concrete compressive strength(MPa, megapascals) ']

# Standardize the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Initialize the Linear Regression model
model = LinearRegression()

# Train the model
model.fit(X_train, y_train)

# Predict on the test set
y_pred = model.predict(X_test)

# Calculate metrics
r2 = r2_score(y_test, y_pred)
mae = mean_absolute_error(y_test, y_pred)
rmse = np.sqrt(mean_squared_error(y_test, y_pred))

print('R-squared:', r2)
print('Mean Absolute Error:', mae)
print('Root Mean Squared Error:', rmse)


# QUALITY OF DATA AND STATISTICS BROKEN DOWN:

#  R-squared: 0.6275416055429018
# Mean Absolute Error (MAE): 7.7453928724213466
# Root Mean Squared Error (RMSE): 9.796707832398448

# In[ ]:


#indicate the model's performance on the test set. The R-squared value suggests that the model explains approximately 62.75% of the variance in the target variable.
#The MAE and RMSE provide information on the average error in the predictions.


# INPUT DATA INTERFACE:

# In[6]:


from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, mean_absolute_error, r2_score
import numpy as np
# Define a function to make predictions using the trained model

def predict_strength(input_features):
    # Standardize the features
    input_features_scaled = scaler.transform(input_features)
    # Make predictions
    strength_pred = model.predict(input_features_scaled)
    return strength_pred

# New mixtures data
new_mixtures = np.array([
    [175.0, 13.0, 172.0, 1000.0, 856.0, 156.0, 4.0, 3.0],
    [320.0, 0.0, 0.0, 970.0, 850.0, 192.0, 0.0, 7.0],
    [320.0, 0.0, 126.0, 860.0, 856.0, 209.0, 5.70, 28.0],
    [320.0, 73.0, 54.0, 972.0, 773.0, 181.0, 6.0, 45.0],
    [530.0, 359.0, 200.0, 1145.0, 992.0, 247.0, 32.0, 365.0]
])

# Predict the concrete strength for the new mixtures
predicted_strengths = predict_strength(new_mixtures)

# Output the predicted strengths
for i, strength in enumerate(predicted_strengths):
    print(f'Mixture {i+1} predicted strength: {strength:.2f} MPa')


# In[ ]:




