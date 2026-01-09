import numpy as np

def extract_features(df):
    features = []

    gsr = df["gsr"].values
    temp = df["temp"].values
    hr = df["heart_rate"].values

    features.append(gsr.mean())
    features.append(gsr.std())
    features.append(temp.mean())
    features.append(temp.std())
    features.append(hr.mean())
    features.append(hr.std())

    return np.array(features)
