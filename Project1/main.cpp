#include <iostream>
using namespace std;

#include "./gdal/gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

int main()
{
	//����ͼ��
	GDALDataset* poSrcDS;
	//���ͼ��
	GDALDataset* poDstDS;
	//ͼ��Ŀ�Ⱥ͸߶�
	int imgXlen, imgYlen;
	//����ͼ��·��
	const char* srcPath = "tree.jpg";
	//���ͼ��·��
	const char* dstPath = "res.tif";
	//ͼ���ڴ�洢
	GByte* buffTmp;
	//ͼ�񲨶���
	int i, bandNUm;
	//ע������
	GDALAllRegister();

	//��ͼ��
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//��ȡͼ����,�߶ȺͲ�������
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNUm = poSrcDS->GetRasterCount();
	//�����ȡ�Ľ��
	cout << "Image X Length: " << imgXlen << endl;
	cout << "Image Y Length" << imgYlen << endl;
	cout << "Band Number:" << bandNUm << endl;
	//����ͼ��Ŀ�Ⱥ͸߶ȷ����ڴ�
	buffTmp = (GByte*)CPLMalloc(imgXlen*imgYlen * sizeof(GByte));
	//�������ͼ��
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen, imgYlen, bandNUm, GDT_Byte, NULL);
	//һ�������ε�����,Ȼ��һ�������ε����
	for (i = 0; i < bandNUm; i++)
	{
		//���������1��ʼ
		poSrcDS->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 0, imgXlen, imgYlen, buffTmp, imgXlen, imgYlen, GDT_Byte, 0, 0);
		printf("... ... band %d processing ... ...\n", i);
	}

	//����ڴ�
	CPLFree(buffTmp);
	//�ر�dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS);




	system("pause");
	return 0;
}