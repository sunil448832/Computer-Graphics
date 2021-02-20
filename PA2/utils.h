
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<vector<float>> reshape(float array[]){
    vector<vector<float>>matrix(4,vector<float> (4,0));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            matrix[j][i]=array[i*4+j];
    return matrix;
}
vector<float> multiply(vector<vector<float>> a,vector<float> b){
   vector<float> result(4,0);
    for(int i=0;i<4;i++)
       for(int j=0;j<4;j++)     
            result[i]+=a[i][j]*b[j];
       
    return result;    
}
vector<vector<float>> frustom_cordinates(float xwMin,float xwMax,float ywMin,
											float ywMax,float dnear,float dfar)
{
	vector<float> v1={xwMin,ywMin,-dnear,1};
	vector<float> v2={xwMin,ywMax,-dnear,1};
	vector<float> v3={xwMax,ywMax,-dnear,1};
	vector<float> v4={xwMin,ywMin,-dnear,1};
	vector<float> v5={xwMin*dfar/dnear,ywMin*dfar/dnear,-dfar,1};
	vector<float> v6={xwMin*dfar/dnear,ywMax*dfar/dnear,-dfar,1};
	vector<float> v7={xwMax*dfar/dnear,ywMax*dfar/dnear,-dfar,1};
	vector<float> v8={xwMin*dfar/dnear,ywMin*dfar/dnear,-dfar,1};
	vector<vector<float>>cordinates={v1,v2,v3,v4,v5,v6,v7,v8};
    return cordinates;

}
vector<vector<float>> normalized_cordinates(vector<vector<float>> matrix_proj,vector<vector<float>> frustom_cord){
	vector<vector<float>> vec;
	for (auto v :frustom_cord){
        vec.push_back(multiply(matrix_proj,v));
	}
	return vec;
}

vector<float>  normalize(vector<float> v){
	float norm=v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
    norm=sqrt(norm)+.00000001;
    vector<float> norm_={v[0]/norm, v[1]/norm, v[2]/norm};
    return norm_;
}
vector<float> normal_vec(vector<float> p0,vector<float> p1,vector<float> p2){
	float x0=p0[0], y0=p0[1], z0=p0[2];
	float x1=p1[0], y1=p1[1], z1=p1[2];
	float x2=p2[0], y2=p2[1], z2=p2[2];

	float n0=(y2-y0)*(z1-z0) -(z2-z0)*(y1-y0);
	float n1=-(x2-x0)*(z1-z0) +(x1-x0)*(z2-z0);
	float n2=(x2-x0)*(y1-y0) -(x1-x0)*(y2-y0);
    
    vector<float> norm_=normalize(vector<float> {n0,n1,n2});
    return norm_;
}

float dot_prod(vector<float> norm,vector<float> view){
	float dot=norm[0]*view[0]+norm[1]*view[1]+norm[2]*view[2];
	return dot;
}
vector<float> add(vector<float> a,vector<float> b){
	vector<float> result={a[0]+b[0],a[1]+b[1],a[2]+b[2]};
	return result;
}
vector<float> scaler_multiply(vector<float> a,float s){
	vector<float> result={a[0]*s,a[1]*s,a[2]*s};
	return result;
}
vector<float> vec_multiply(vector<float> a,vector<float> b){
	vector<float> result={a[0]*b[0],a[1]*b[1],a[2]*b[2]};
	return result;
}

vector<float> phong_shadding(vector<float> h,vector<float> n,vector<float> l){
	vector<float> cl={1,1,0};
	vector<float> ca={0,0,1};
	vector<float> cr={.01,.5,.1};
	int p=2;
	float n_l=dot_prod(n,l);
	float h_n=dot_prod(h,n);
	vector<float> c_rl=scaler_multiply(vec_multiply(cl,cr),pow(h_n,p));
	float x=h_n<0? 0:h_n;
    vector<float> c_lm=scaler_multiply(cl,x);
    vector<float> c_al=add(ca,c_lm);
    vector<float> c_rm=vec_multiply(cr,c_al);
    vector<float> color=add(c_rm,c_rl);
    return color;
}

void show(vector<vector<float>> cord){
	for(auto c: cord){
   		for(int i=0 ;i<3;i++) 
   			cout<<c[i]/c[3]<<" ";
   		cout<<endl;
   	}
}

