CREATE DATABASE IF NOT EXISTS smartguard_iot;

USE smartguard_iot;

CREATE TABLE IF NOT EXISTS leituras_iot (
    id INT AUTO_INCREMENT PRIMARY KEY,
    distancia_cm DECIMAL(10,2) NOT NULL,
    luminosidade INT NOT NULL,
    status_aproximacao VARCHAR(50) NOT NULL,
    status_luminosidade VARCHAR(50) NOT NULL,
    status_geral VARCHAR(50) NOT NULL,
    data_hora TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);


SELECT * FROM leituras_iot
ORDER BY id DESC
LIMIT 20;
