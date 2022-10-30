# Hashdog

<br>

## Installation guide

1. Install requirements : <br> `apt install gcc make libssl-dev`

2. Compile : <br> `make`

3. Run program : <br> `./hashdog -h`

<br>

## Docker usage

1. Build image : <br> `make docker_build` or `sudo docker build -t hashdog .`

2. Run container :  <br> `make docker_run` or `sudo docker run -t -d --name hashdog hashdog`

3. Enter container : <br> `make docker_exec` or `sudo docker exec -it hashdog bash`

4. Run program : `./hashdog -h`

5. Stop container : <br> `make docker_stop` or `sudo docker stop hashdog`

6. Remove container : <br> `make docker_rm` or `sudo docker rm hashdog`

To remember :
- Copy file from host to container : `sudo docker cp <file> hashdog:/app/`
- Copy file from container to host : `sudo docker cp hashdog:/app/<file> .`

<br>

## Hashdog usage

Print help message : <br> `./hashdog -h`

![alt text](./doc/img/hashdog_usage_1.png)

Generate hashes from user input : <br> `./hashdog -m generate -d sha256` 

![alt text](./doc/img/hashdog_usage_2.png)

Generate hashes from dictionnary : <br> `./hashdog -m generate -d sha256 -f dictionnary/rockyou.txt`

![alt text](./doc/img/hashdog_usage_3.png)

Generate T3C from dictionnary : <br> `./hashdog -m generate -d sha256 -f dictionnary/rockyou.txt -o t3c/rockyou.t3c`

![alt text](./doc/img/hashdog_usage_4_1.png)

![alt text](./doc/img/hashdog_usage_4_2.png)

Load T3C file and lookup hashes : <br> `./hashdog -m lookup -f t3c/rockyou.t3c`

![alt text](./doc/img/hashdog_usage_5.png)
