/**************************
* 
* 输入参数处理的实践
* 选项 参数    功能
* -t   无      仅测试
* -s   string  输出一个字符串
* -c   int int 计算两个参数之和并输出
*
***************************/

#include <stdio.h>
#include "process.h"


typedef struct {
    int argc;
    char *const *argv;
} process_ctx;


int deal_by_ctx(process_ctx *ctx);
int stoi(const char *s, int *i);


int main(int argc, char *const *argv) {

	process_ctx ctx;

	ctx.argc = argc;
	ctx.argv = argv;

	printf("====== process begin =====\n");

	if (deal_by_ctx(&ctx) == PRO_OK) {
		printf("====== success =====\n");

	} else {
		printf("====== fail =====\n");
	}

	printf("====== process ended =====\n");

    return 0;
}


int deal_by_ctx(process_ctx *ctx) {

	int i, a, b, argc = ctx->argc;
	char *const *argv = ctx->argv;

	for (i = 1; i < argc; i++) {

		if (argv[i][0] != '-') {
			return PRO_ERR;
		}

		switch(argv[i][1]) {

		case 't':
			printf("====== just test ======\n");
			break;

		case 's':
			printf("====== %s ======\n", argv[++i]);
			break;

		case 'c':
			if (stoi(argv[++i], &a) != PRO_OK) {
				return PRO_ERR;
			}

			if (stoi(argv[++i], &b) != PRO_OK) {
				return PRO_ERR;
			}

			printf("====== equal: %d ======\n", a + b);
			break;

		default:
			return PRO_ERR;
		}
	}

	return PRO_OK;
}


int stoi(const char *s, int *i) {
	
	*i = 0;

	while(*s != '\0') {

		if (*s >= '0' && *s <= '9') {
			*i = *i * 10 + (*s++ - '0'); 

		} else {
			return PRO_ERR;
		}
	}

	return PRO_OK;
}
