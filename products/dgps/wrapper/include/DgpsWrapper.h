
#include "DgpsData.h"
#include "IWrapper.h"

/**

 * */
class DgpsWrapper : public IWrapper<DgpsData> {
private:
    DgpsData m_data;
    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    DgpsWrapper();

    ~DgpsWrapper();

    /**
     * Calls vlp->run
     */ 
    virtual void Run() override;

    /**
     * Take the temporary data and set it to vlp
     */ 
    virtual void SetData() override;

    void SetDgpsData(const DgpsData& data) {
        m_data = data;
    }
};