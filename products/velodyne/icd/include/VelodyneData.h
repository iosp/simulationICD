#ifndef VELODYNE_DATA_H
#define VELODYNE_DATA_H

/*
* VelodyneData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::time_duration


class VelodyneData {
public:
    /**
     * VLP data to get and save 
     */  
    class VLPBlock {
    public:  typedef std::vector<std::pair<double, short> > t_channel_data;
    private:
        double m_azimuth;
        t_channel_data m_channels;
        boost::posix_time::time_duration m_simTime;

    public:
        VLPBlock() = default;

        VLPBlock(double azimuth, const t_channel_data& channels, const boost::posix_time::time_duration& simTime);

        ~VLPBlock() = default;

        double GetAzimuth() const {
            return m_azimuth;
        }
        
        void SetAzimuth(double azimuth) {
            m_azimuth = azimuth;
        }

        const t_channel_data& GetChannels() const {
            return m_channels;
        }

        void SetChannels(const t_channel_data& channels) {
            m_channels = channels;
        }

        const boost::posix_time::time_duration& GetSimTime() const {
            return m_simTime;
        }

        void SetSimTime(const boost::posix_time::time_duration& simTime) {
            m_simTime = simTime;
        }
    };

private:
    /**
     * Holds multiple data blocks
     */ 
    std::vector<VLPBlock> m_data;

public:
    VelodyneData() = default;

    VelodyneData(const std::vector<VLPBlock>& data);
    
    ~VelodyneData() = default;

    const std::vector<VLPBlock>& GetData() const {
        return m_data;
    }
};



#endif // VELODYNE_DATA_H