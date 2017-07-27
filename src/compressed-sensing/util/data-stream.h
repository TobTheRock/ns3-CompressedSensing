/**
* \file data-stream.h
*
* \author Tobias Waurick
* \date 26.07.17
*
*/
#ifndef DATA_STREAM_H
#define DATA_STREAM_H

#include <string>
#include <vector>
#include "ns3/simple-ref-count.h"
#include "serial-buffer.h"

/**
* \ingroup util
* \class DataStream
*
* \brief A data storage class with multiple streams and a group name
*
* This class can be used to pass data via  SerialDataBuffer instances easily to other classes.
* Those buffers are grouped in this class and are given a group name which can be used for writting/reading to/from external files.
*
* \tparam type of data stored
*/
template <typename T>
class DataStream : public ns3::SimpleRefCount<DataStream<T>>
{
  public:
	typedef SerialDataBuffer<T> T_Buffer;					/**< Type of the underlying buffers*/
	typedef std::vector<T_Buffer>::const_iterator Iterator; /**< Iterator over all buffers*/

	/**
	* \brief creates a DataStream with a name and no elements
	*
	* \param name name of this DataStream
	*
	*/
	DataStream(std::string name) : m_name(name){};

	/**
	* \brief Adds a SerialDataBuffer
	*
	* \param buffer pointer to SerialDataBuffer to add
	*
	*/
	void AddBuffer(Ptr<T_Buffer> buffer)
	{
		m_dataStreams.push_back(buffer);
	};

	/**
	* \brief Gets a stored SerialDataBuffer at the given index	and removes it
	*
	* \param idx index of stored SerialDataBuffer
	*
	* \return pointer to SerialDataBuffer
	*/
	Ptr<T_Buffer> GetBuffer(uint32_t idx) const
	{
		Ptr<T_Buffer> out = m_dataStreams.at(idx);
		m_dataStreams.erase(idx);
		return out;
	};

	/**
	* \brief Gets a stored SerialDataBuffer at the given index	and keeps it stored
	*
	* \param idx index of stored SerialDataBuffer
	*
	* \return pointer to SerialDataBuffer
	*/
	Ptr<T_Buffer> PeekBuffer(uint32_t idx) const
	{
		return m_dataStreams.at(i);
	};

	/**
	* \brief Gets the NOF SerialDataBuffer stored
	*
	* \return NOF SerialDataBuffer stored
	*/
	uint32_t GetN()
	{
		return m_dataStreams.size();
	};

	/**
	* \brief gets the name of this DataStream
	*
	* \return name of this DataStream
	*/
	std::string GetName()
	{
		return m_name;
	};

	/**
	* \brief get the iterator's beginning over all stored SerialDataBuffer elements
	*
	* \return iterator to beginning 
	*/
	Iterator Begin()
	{
		return m_dataStreams.begin();
	};

	/**
	* \brief get the iterator's ending over all stored SerialDataBuffer elements
	*
	* \return iterator to end
	*/
	Iterator End()
	{
		return m_dataStreams.end();
	};

  private:
	std::string m_name;						  /**< name of the DataStream*/
	std::vector<Ptr<T_Buffer>> m_dataStreams; /**< stored SerialDataBuffer instances*/
};

/**
* \ingroup util
* \class DataStreamContainer
*
* \brief container class for DataStream instances
*
* \tparam type of data stored
*/
template <typename T>
class DataStreamContainer : public ns3::SimpleRefCount
{
  public:
	typedef std::vector<Ptr<DataStream<T>>>::const_iterator Iterator;

	/**
	* \brief creates an empty DataStreamContainer
	*
	*/
	DataStreamContainer(){};

	/**
	* \brief Append the contents of another DataStreamContainer<T> to the end of
	* this container.
	*
	* \param other The DataStreamContainer<T> to append.
	*/
	void Add(DataStreamContainer<T> other)
	{
		for (Iterator i = other.Begin(); i != other.End(); i++)
		{
			m_dataStreams.push_back(*i);
		}
	};

	/**
   * \brief Append a single Ptr<DataStream<T>> to this container.
   *
   * \param stream The Ptr<DataStream<T>> to append.
   */
	void Add(Ptr<DataStream<T>> stream)
	{
		m_dataStreams.push_back(stream);
	};

	/**
	* \brief Gets the NOF DataStream instances stored
	*
	* \return NOF DataStream instances stored
	*/
	uint32_t GetN()
	{
		return m_dataStreams.size();
	};

	/**
	* \brief get the iterator's beginning over all stored DataStream elements
	*
	* \return iterator to beginning 
	*/
	Iterator Begin()
	{
		return m_dataStreams.begin();
	};

	/**
	* \brief get the iterator's ending over all stored DataStream elements
	*
	* \return iterator to end
	*/
	Iterator End()
	{
		return m_dataStreams.end();
	};

  private:
	std::vector<Ptr<DataStream<T>>> m_dataStreams; /**< stored DataStream instances*/
};

#endif //DATA_STREAM_H