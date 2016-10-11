CC = cc
CCFLAGS = -Wall -g -ggdb

CMM_OBJ=sock.o util.o

SOLINGER_SVR_EXE=sock-svr-solinger
SOLINGER_CLT_EXE=sock-clt-solinger

SOLINGER_SVR_OBJ=$(CMM_OBJ) sock-svr-solinger.o
SOLINGER_CLT_OBJ=$(CMM_OBJ) sock-clt-solinger.o

URGENT_SVR_EXE=sock-svr-urgent
URGENT_CLT_EXE=sock-clt-urgent

URGENT_SVR_OBJ=$(CMM_OBJ) sock-svr-urgent.o
URGENT_CLT_OBJ=$(CMM_OBJ) sock-clt-urgent.o


MYEXE=$(SOLINGER_SVR_EXE) $(SOLINGER_CLT_EXE) \
       $(URGENT_SVR_EXE) $(URGENT_CLT_EXE)


EXT_CCFLAGS = 

all:$(MYEXE)

$(SOLINGER_SVR_EXE):$(SOLINGER_SVR_OBJ)
	$(CC) -o $@ $^ $(EXT_CCFLAGS) 
$(SOLINGER_CLT_EXE):$(SOLINGER_CLT_OBJ)
	$(CC) -o $@ $^ $(EXT_CCFLAGS) 
	
$(URGENT_SVR_EXE):$(URGENT_SVR_OBJ)
	$(CC) -o $@ $^ $(EXT_CCFLAGS) 
$(URGENT_CLT_EXE):$(URGENT_CLT_OBJ)
	$(CC) -o $@ $^ $(EXT_CCFLAGS) 


clean:
	rm -rf *.o
	rm -rf $(MYEXE)

.PRECIOUS:%.c
.SUFFIXES:
.SUFFIXES:.c .o
.c.o:
	$(CC) $(CCFLAGS) -c -o $*.o $<

