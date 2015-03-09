#pragma once

#include <vector>
using std::vector;

#define VDP void*

class ListGeneric
{
public:
	ListGeneric() {}
	~ListGeneric() {datalist.clear();}


	void	Add(VDP pData){datalist.push_back(pData);}
	int 	ListSize(){return (int)datalist.size();}
	VDP		Get(int i){return datalist[i];}

	void Remove(int i)
	{
		delete datalist[i];
		vector<VDP>::iterator itr1 = datalist.begin();
		itr1 += i;
		datalist.erase(itr1);
	}

	void Set(int i, VDP pData){
		datalist[i] = pData;
	}

	void Clear(){
		datalist.clear();
	}

private:
	vector<VDP> datalist;
};

#define AddToList( datalist, dataref ) datalist.Add( (void*)dataref )
#define GetFromList(DATATYPE, datalist, index  ) (DATATYPE*)datalist.Get(index)
