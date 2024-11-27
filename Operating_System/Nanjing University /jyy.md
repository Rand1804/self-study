an implementation of the Towers of Hanoi puzzle using an explicit stack to avoid recursion:
manual stack management

```C
typedef struct {
	int pc, n;
	char from, to, via;
} Frame;

#define call(...) ({ *(++top) = (Frame) { .pc = 0, __VA_ARGS__ }; })

#define ret() ({ top--; })

#define goto(loc) ({ f->pc = (loc) - 1; })

void hanoi(int n, char from, char to, char via) {

	Frame stk[64], *top = stk - 1;
	
	call(n, from, to, via);
	
	for (Frame *f; (f = top) >= stk; f->pc++) {
	
	n = f->n; from = f->from; to = f->to; via = f->via;
	
	switch (f->pc) {
	
		case 0: if (n == 1) { printf("%c -> %c\n", from, to); goto(4); } break;
		
		case 1: call(n - 1, from, via, to); break;
		
		case 2: call( 1, from, to, via); break;
		
		case 3: call(n - 1, via, to, from); break;
		
		case 4: ret(); break;
	
		default: assert(0);

		}

	}

}
```

### 条件变量和状态机用法示例(打印鱼字符)

```c
#include "thread.h"

#include "thread-sync.h"

  

#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

  

enum { A = 1, B, C, D, E, F, };

  

struct rule {

int from, ch, to;

} rules[] = {

{A, '<', B},

{B, '>', C},

{C, '<', D},

{A, '>', E},

{E, '<', F},

{F, '>', D},

{D, '_', A},

};

  

int current = A, quota = 1;

  

mutex_t lk = MUTEX_INIT();

cond_t cv = COND_INIT();

  

int next(char ch) {

for (int i = 0; i < LENGTH(rules); i++) {

struct rule *rule = &rules[i];

if (rule->from == current && rule->ch == ch) {

return rule->to;

}

}

return 0;

}

  

static int can_print(char ch) {

return next(ch) != 0 && quota > 0;

}

  

void fish_before(char ch) {

mutex_lock(&lk);

while (!can_print(ch)) {

cond_wait(&cv, &lk);

}

quota--;

mutex_unlock(&lk);

}

  

void fish_after(char ch) {

mutex_lock(&lk);

quota++;

current = next(ch);

assert(current);

cond_broadcast(&cv);

mutex_unlock(&lk);

}

  

const char roles[] = ".<<<<<>>>>___";

  

void fish_thread(int id) {

char role = roles[id];

while (1) {

fish_before(role);

putchar(role); // Not lock-protected

fish_after(role);

}

}

  

int main() {

setbuf(stdout, NULL);

for (int i = 0; i < strlen(roles); i++)

create(fish_thread);

}
```

### 用条件变量实现信号量
- `sem->count > 0`
```c

void P(sem_t *sem) {
	hold(&sem->mutex) {
		while (!COND) {
			cond_wait(&sem->cv, &sem->mutex);
		sem->count--;
		}
	}
}

void V(sem_t *sem) {
	hold(&sem->mutex) {
		sem->count++;
		cond_brodcast(&sem->cv);
	}
}

```

### 用信号量实现条件变量
```c

/* 很难实现,该实现不正确 */
void wait(struct condvar *cv, mutex_t *mutex) 
{
	mutex_lock(&cv->lock);
	cv->nwait++;
	mutex_unlock(&cv->lock);

	//! BUGGY
	// release-wait 必须实现成原子操作
	
	mutex_unlock(mutex);
	// 在释放锁之后发生broadcast,则会造成死锁
	P(&cv->sleep);

	mutex_lock(mutex);
}


void broadcast(struct condvar *cv)
{
	mutex_lock(&cv->lock);

	for(int i = 0; i < cv->nwait; i++) {
		V(&cv->sleep);
	}
	cv->nwait = 0;

	mutex_unlock(&cv->lock);

}



```