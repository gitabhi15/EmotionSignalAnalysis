import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from load_data import load_csv
from preprocess import normalize, clean
from features import extract_features

def main():
    df = load_csv("data/sample_data.csv")
    df = clean(df)
    df = normalize(df)

    X = []
    y = []

    for label in df["label"].unique():
        chunk = df[df["label"] == label]
        feats = extract_features(chunk)
        X.append(feats)
        y.append(label)

    X = np.array(X)
    y = np.array(y)

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.3, random_state=42
    )

    model = SVC(kernel="linear")
    model.fit(X_train, y_train)

    preds = model.predict(X_test)
    acc = accuracy_score(y_test, preds)

    print("accuracy", acc)

    return model

if __name__ == "__main__":
    main()
