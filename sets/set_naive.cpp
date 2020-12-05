// DSU Naive

void makeset(vector<int> &smallest,int i){
	smallest[i] = i;
}

void Find(vetor<int>&smallest,int i){
	return smallest[i];
}

// Take union of set of 2 elements 
void Union(vector<int>&smallest,int i,int j){
	int i_id = Find(smallest,i);
	int j_id = Find(smallest,j);

	if (i_id==j_id)
		return;

	int m = min(i_id,j_id);

	for (int k=1;k<n;++i){
		if (smallest[i]==i_id || smallest[i]==j_id)
			smallest[k] = m;
	}
}

