# 定义变量
src=$(wildcard ./*.c)
objs=$(patsubst %.c, %.o, $(src))
target=app

$(target):$(objs)
	$(CC) $(objs) -o $(target)

%.o:%.c
	$(CC) -c $< -o $@

clean:
	rm $(objs) -f
