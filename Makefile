docker-build:
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.yml \
	build

blank-map:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.basic.yml \
	up

route-old:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.yml \
	up

route:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.yml \
	run cpp

tests:
	xhost + 127.0.0.1
	docker-compose \
	-p cpp-route-planning \
	-f dcomposes/docker-compose.test.yml \
	up
