CONTAINER_NAME=nand2tetris
SERVICE_NAME=nand2tetris

stop:
	docker-compose stop $(CONTAINER_NAME)

down:
	docker-compose down

build:
	docker-compose build

up:
	docker-compose up -d

exec:
	docker-compose exec $(SERVICE_NAME) bash