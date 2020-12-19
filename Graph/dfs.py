# undirected 

def addEdge(G,u:int,v:int):
	G[u][v] = 1
	G[v][u] = 1


if __name__=="__main__":
	n,m = map(int,input().split())
    
    # n vertices m edges

    G = [[0 for i in range(n)] for i in range(n)]

    u,v = 0,0

    for i in range(m):
    	u,v = map(int,input().split())
    	G[u][v]=1
    	G[v][u]=1

    	