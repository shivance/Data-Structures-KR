class trienode:
    
    def __init__(self,size):
        self.eow = False
        self.s = size
        self.child = [None]*size
        

    
def printvec(l):
    for i in l:
        print(i,end="")


def insert(T,m,string):
    idx = 0
    tmp = T
    
    for i in range(len(string)):
        idx = m.index(string[i]) - 0
    
        if tmp.child[idx] == None:
            tmp.child[idx] = trienode(len(m))
        tmp = tmp.child[idx] 

    tmp.eow = True

def printTr(T,m,stk):
    if (T==None or T.eow):
        printvec(stk)
        print()

        if T==None:
            for i in range(T.s):
                if (i):
                    print(m[i])
            print(end = "")

        return

    for i in range(T.s):
        if (T.child[i]):
            stk.append(m[i])
            printTr(T.child[i],m,stk)
            stk.pop()



if __name__=="__main__":
    o = False
    vec = []
    m = set()

    while True:
        s = str(input())
        if (s[-1]=='#'):
            o = True
            s = s[:-1]
        vec.append(s)
        for i in s:
            m.add(i)
        if o:
            break

    keys = list()
    m = sorted(list(m))
   
    T = trienode(len(m))
    stk = list()

    for i in vec:
        insert(T,m,i)
        
    print("TRIE : ")
    printTr(T,m,stk)

'''
abd5c2
ac8b9
cdd294a1
da5b4c63
bd367#
'''