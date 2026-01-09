import numpy as np
from features import extract_features

def predict_emotion(model, df):
    feats = extract_features(df)
    feats = feats.reshape(1, -1)
    pred = model.predict(feats)
    return pred[0]
