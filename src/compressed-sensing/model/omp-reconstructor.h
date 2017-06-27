/**
* \file omp-reconstructor.cc
*
* \author Tobias Waurick
* \date 20.06.17
*
*/

#ifndef OMP_RECONSTRUCTOR
#define OMP_RECONSTRUCTOR
#include "reconstructor.h"
using namespace kl1p;

typedef Reconstructor::T_NodeIdTag T_NodeIdTag;

class OMP_TempReconstructor : public Reconstructor
{
  public:
	static TypeId GetTypeId(void);

	OMP_TempReconstructor();
	/**
	* \brief setups the reconstructors attributes
	*
	* \param nMeas 		original length of/(NOF) each original measurment (vectors)
	* \param mMax  		maximum length of/(NOF)  measurments (vectors) used for reconstructing
	* \param k			sparsity of solution
	* \param tolerance	tolerance of solution
	*
	*/
	void Setup(uint32_t nMeas, uint32_t mMax, uint32_t k, double tolerance);

	/**
	* \brief Adds a source node whose measurement data shall be reconstructed
	*
	* \param nodeId		8bit node Id
	* \param seed 		Seed used for constructing the sensing matrix of each node
	* \param nMeas 		original length of/(NOF) each original measurment (vectors)
	* \param mMax  		maximum length of/(NOF)  measurments (vectors) used for reconstructing
	*
	*/
	void AddSrcNode(T_NodeIdTag nodeId, uint32_t seed, uint32_t nMeas, uint32_t mMax);
	using Reconstructor::AddSrcNode;
	/**
	* \brief write a data sample to the input buffer
	*
	* \param nodeId 8bit ID of node
	* \param data   data value	
	*
	* \return remaining size of buffer
	*/
	uint32_t Write(T_NodeIdTag nodeId, double data);

	/**
	* \brief starts the reconstruction for one node with given sparsity
	*
	* \param nodeId ID of node to reconstruct
	* \param kspars	sparsitiy of solution(if 0 : assumed to be m/2)
	* \param iter	iteration limit (if 0 : no Limit)
	* 
	* \return time in ms needed for reconstruction
	*/
	virtual int64_t  Reconstruct(T_NodeIdTag nodeId, uint32_t kspars, uint32_t iter=0);

	/**
	* \brief starts the reconstruction for one node with default sparsity
	*
	* \param nodeId ID of node to reconstruct
	* 
	* \return time in ms needed for reconstruction
	*/
	virtual int64_t  Reconstruct(T_NodeIdTag nodeId);

	/**
	* \brief starts the reconstruction for all nodes
	*
	* \return time in ms needed for reconstruction
	*/
	virtual int64_t  ReconstructAll();

  private:
	double m_tolerance; /**< tolerance of solution*/
	uint32_t m_kDef;	/**< sparsity of solution*/
};

#endif //OMP_TEMP_RECONSTRUCTOR