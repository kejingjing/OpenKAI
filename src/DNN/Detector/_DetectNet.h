/*
 * _DetectNet.h
 *
 *  Created on: Aug 17, 2016
 *      Author: yankai
 */

#ifndef OPENKAI_SRC_DNN__DetectNet_H_
#define OPENKAI_SRC_DNN__DetectNet_H_

#include "../../Base/common.h"
#include "../../Vision/_VisionBase.h"
#include "_DNNdetectorBase.h"

namespace kai
{

class _DetectNet: public _DNNdetectorBase
{
public:
	_DetectNet();
	~_DetectNet();

	bool init(void* pKiss);
	bool link(void);
	bool start(void);
	bool draw(void);

private:
	void detect(void);
	void addOrUpdate(OBJECT* pNewObj);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_DetectNet*) This)->update();
		return NULL;
	}

public:
#ifdef USE_TENSORRT
	detectNet* m_pDN;
#endif
	int m_nBox;
	int m_nBoxMax;
	uint32_t m_nClass;

	int num_channels_;
	cv::Mat mean_;
	Frame* m_pRGBA;
	Frame* m_pRGBAf;
	double m_minCofidence;

	double m_minSize;
	double m_maxSize;
	double m_overlapMin;
	vDouble4 m_area;

	float* m_bbCPU;
	float* m_bbCUDA;
	float* m_confCPU;
	float* m_confCUDA;

	string m_className;

};

}

#endif
