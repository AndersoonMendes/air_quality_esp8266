import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import emlearn

# calculo da aqi baseado no pm2.5
def calcular_aqi(pm25):
    faixas = [
        (0.0, 9.0, 0, 50),
        (9.1, 35.4, 51, 100),
        (35.5, 55.4, 101, 150),
        (55.5, 125.4, 151, 200),
        (125.5, 225.4, 201, 300),
        (225.5, 325.4, 301, 500)
    ]

    if pm25 < 0:
        return np.nan

    for c_lo, c_hi, i_lo, i_hi in faixas:
        if c_lo <= pm25 <= c_hi:
            return round(
                ((i_hi - i_lo) / (c_hi - c_lo))
                * (pm25 - c_lo) + i_lo
            )

    return np.nan

np.random.seed(42)
n = 100

# classe 0: Bom — AQI 0 a 50
pm25_bom = np.random.normal(loc=5, scale=2, size=n)
pm25_bom = np.clip(pm25_bom, 0, 9.0)
labels_bom = np.zeros(n)

# classe 1: Moderado — AQI 51 a 100
pm25_moderado = np.random.normal(loc=22, scale=6, size=n)
pm25_moderado = np.clip(pm25_moderado, 9.1, 35.4)
labels_moderado = np.ones(n)

# classe 2: Insalubre para grupos sensíveis — AQI 101 a 150
pm25_ruim = np.random.normal(loc=45, scale=5, size=n)
pm25_ruim = np.clip(pm25_ruim, 35.5, 55.4)
labels_ruim = np.full(n, 2)

# classe 3: Insalubre — AQI 151 a 200
pm25_muito_ruim = np.random.normal(loc=90, scale=15, size=n)
pm25_muito_ruim = np.clip(pm25_muito_ruim, 55.5, 125.4)
labels_muito_ruim = np.full(n, 3)

# classe 4: Muito insalubre — AQI 201 a 300
pm25_pessimo = np.random.normal(loc=175, scale=20, size=n)
pm25_pessimo = np.clip(pm25_pessimo, 125.5, 225.4)
labels_pessimo = np.full(n, 4)

# criação do DataFrame
df = pd.DataFrame({
    'pm25 value': np.concatenate([
        pm25_bom,
        pm25_moderado,
        pm25_ruim,
        pm25_muito_ruim,
        pm25_pessimo
    ]),
    'labels': np.concatenate([
        labels_bom,
        labels_moderado,
        labels_ruim,
        labels_muito_ruim,
        labels_pessimo
    ])
})
print(df)

#####################################################
# engenhraria de recursos, calculando o aqi com os valores da coluna pm25 value
df['aqi'] = df['pm25 value'].apply(calcular_aqi)

print(df)

#########################################
# definindo dados de trino
X = df[['pm25 value']]
y = df[['labels']]

X_treino, X_teste, y_treino, y_teste = train_test_split(X, y, test_size=0.2, random_state=42)

# treinando o modelo
modelo = RandomForestClassifier(n_estimators=10, random_state=42)

modelo.fit(X_treino, y_treino)

# avaliando o desempenho
y_pred = modelo.predict(X_teste)
acuracia = accuracy_score(y_teste, y_pred)

print(f"\n--- RESULTADO DA AVALIAÇÃO ---")
print(f"Acurácia do Modelo nos dados de teste: {acuracia * 100:.2f}%")

# testando o novo dado
valor_sensor = 150.4
nova_leitura = [[valor_sensor]]
previsao = modelo.predict(nova_leitura)

print(f"\n[Leitura do sensor]: {valor_sensor}")
qualidade = {0: "bom", 1: "moderado", 2: "ruim", 3: "muito ruim", 4: "pessimo"}

print(f"[PREVISÂO DA IA]: o ar esta -> {qualidade[previsao[0]]}")


# --- 3. CONVERTENDO PARA C/C++ COM EMLEARN ---
c_model = emlearn.convert(modelo)
# Salvando o modelo no arquivo 'modelo_pm25.h'
c_model.save(file='modelo_pm25.h', name='modelo_pm25')

print("Arquivo 'modelo_pm25.h' gerado com sucesso!")