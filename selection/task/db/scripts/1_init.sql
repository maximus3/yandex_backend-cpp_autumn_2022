CREATE TABLE IF NOT EXISTS system_item(
            uid SERIAL PRIMARY KEY,
            id VARCHAR(255) NOT NULL UNIQUE,
            url VARCHAR(255),
            date VARCHAR(255) NOT NULL,
            dt_date TIMESTAMP NOT NULL,
            CONSTRAINT parentId FOREIGN KEY (id) REFERENCES system_item (id) ON DELETE CASCADE,
            type VARCHAR(255) NOT NULL,
            size BIGINT
            );