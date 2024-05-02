# PostgreSQLのextension作成例

```sh
# ビルド
docker compose build

# 起動
docker compose up -d

# 実行
docker compose exec -it db psql -h localhost -U postgres

# テスト実行（起動中に）
docker compose exec -it db sh -c 'PGUSER=postgres make USE_PGXS=1 PG_CONFIG=/usr/bin/pg_config installcheck'
```
