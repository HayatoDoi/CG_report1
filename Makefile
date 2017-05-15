SRCS = planet.c

# 実行ファイル名(ソースコード名から拡張子を抜いた)
EXES = $(SRCS:.c=)
LESSFILE = ${EXES}.lss
# コンパイル
${EXES} : ${SRCS}
	gcc ${SRCS} -o ${EXES} -Wall  -lglut -lGLU -lGL -lm 
	objdump -M intel -d ${EXES} > ${LESSFILE}
# すべて綺麗に!!
clean : 
	rm ${EXES} ${LESSFILE}
