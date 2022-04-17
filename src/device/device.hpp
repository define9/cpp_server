#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "visa/visa.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/fmt.h"
#include <vector>
#include <string>

namespace {
    const std::string kParamString[] = {
        "CURR", "VOLT"
    };

    enum Param{
        CURR = 0,
        VOLT
    };
}

class Device
{
public:
    //设备标识码
    ViSession ins_;

    bool isRunning_ = false;
public:
    Device();

    int OpenDev(char *address);

    int CloseDev();

    /**
     * @brief FindAllRsrc 得到 可以控制的Visa设备
     * @return
     */
    std::vector<std::string> FindAllRsrc();

    /**
     * @brief ReadData  读取数据
     * @param param     电流\电压 Param
     * @param channel   通道, 0 为无通道
     * @return 读取的数据
     */
    double ReadData(Param param = Param::CURR, uint8_t channel = 1);

    ViStatus SendInstructions(const std::string &cmd);
};

inline int Device::OpenDev(char *address) {
    char stringinput[100];
    ViSession defaultRM_;
    viOpenDefaultRM(&defaultRM_);

    viOpen(defaultRM_, ViRsrc(address), VI_NULL, VI_NULL, &ins_);

    // TODO 验证defaultRM_ 需不需要close或者持久到类内

    //获取设备标识码
    ViStatus status = SendInstructions("*IDN?");
    if (status != 0){
        SPDLOG_ERROR("SendInstructions('*IDN?') error, status_ is {}", status);
    }
    status = viRead(ins_, ViBuf(stringinput), 100, VI_NULL);
    if (status != 0){
        SPDLOG_ERROR("ViRead error, status_ is {}", status);
    }
    return status;
}

inline int Device::CloseDev() {
    ViStatus status;
    SendInstructions("OUTP1 OFF");
//    SendInstructions("OUTP2 OFF");
    status = viClose(ins_);
    // viClose(defaultRM_);
}

inline std::vector<std::string> Device::FindAllRsrc() {
    std::vector<std::string> address;
    ViSession defaultRM;
    ViFindList deviceLists;
    ViUInt32 size = 0;
    ViChar desc[200] = "";
    ViSession ins;

    int status = viOpenDefaultRM(&defaultRM);
    // TODO 此处更改超时时间 连接不需要长时间
    status = viFindRsrc(defaultRM, "?*INSTR", &deviceLists, &size, desc);
    SPDLOG_INFO("findRsrc: status_ is {}, size is {}", status, size);
    SPDLOG_INFO("primay address is {}", std::string(desc));
    if (0 == viOpen(defaultRM, desc, VI_NULL, VI_NULL, &ins)){
        address.push_back(desc);
        viClose(ins);
    }

    for (ViUInt32 i = 0;i < size - 1;i++) {
        status = viFindNext(deviceLists, desc);
        status += viOpen(defaultRM, desc, VI_NULL, VI_NULL, &ins);
        viClose(ins);
        SPDLOG_INFO("deviceAddress : {}", std::string(desc));
        // SPDLOG_INFO("deviceAddress status: {}", status);
        if (status == 0){
            address.push_back(desc);
        }
    }
    viClose(deviceLists);
    viClose(defaultRM);

    return address;
}

inline double Device::ReadData(Param param, uint8_t channel) {
    viFlush(ins_, VI_READ_BUF);
    char Data[100];
    ViStatus status = SendInstructions(fmt::format("MEAS:{}? (@{})", kParamString[param],  channel));
    status = viRead(ins_, ViBuf(Data), 100, nullptr);

    if(status != 0) {
        SPDLOG_ERROR("ReadData Error: {}", status);
        return 0;
    }

    return strtod(Data, nullptr);
}

inline ViStatus Device::SendInstructions(const std::string &cmd) {
    ViStatus status = viWrite(ins_, ViBuf(cmd.c_str()), cmd.size(), VI_NULL);
    if (status != 0)
        SPDLOG_ERROR("SendInstructions Error: {}", status);
    return status;
}

#endif // DEVICE_HPP
