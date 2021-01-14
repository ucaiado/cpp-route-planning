docker-build:
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.yml \
	build

basic:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.basic.yml \
	up

up:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.yml \
	up

test:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.test.yml \
	up
