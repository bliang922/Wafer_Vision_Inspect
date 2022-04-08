#ifndef _LEISAI_IOC0640_H
#define _LEISAI_IOC0640_H

//定义输入和输出
#ifdef __IOC0640_EXPORTS
	#define IOC0640_API __declspec(dllexport)
#else
	#define IOC0640_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//中断回调函数指针定义
typedef unsigned int        UINT;
typedef UINT (__stdcall *IOC0640_OPERATE)(PVOID operate_data);



//---------------------   板卡初始和配置函数  ----------------------
/********************************************************************************
** 函数名称: ioc_board_init
** 功能描述: 控制板初始化，设置初始化和速度等设置
** 输　  入: 无
** 返 回 值: 0：无卡； 1-8：成功(实际卡数) 
**     
*********************************************************************************/
IOC0640_API int __stdcall ioc_board_init(void);

/********************************************************************************
** 函数名称: d2c80_board_close
** 功能描述: 关闭所有卡
** 输　  入: 无
** 返 回 值: 无
** 日    期: 2007.02.1
*********************************************************************************/
IOC0640_API void __stdcall ioc_board_close(void); 

//IO控制函数
IOC0640_API int __stdcall ioc_read_inbit(WORD cardno, WORD bitno);
IOC0640_API int __stdcall  ioc_read_outbit(WORD cardno, WORD bitno);
IOC0640_API DWORD __stdcall ioc_write_outbit(WORD cardno, WORD bitno,WORD on_off);

IOC0640_API long __stdcall ioc_read_inport(WORD cardno,WORD m_PortNo);
IOC0640_API long __stdcall ioc_read_outport(WORD cardno,WORD m_PortNo) ;
IOC0640_API DWORD __stdcall ioc_write_outport(WORD cardno,WORD m_PortNo, DWORD port_value);

IOC0640_API DWORD __stdcall ioc_int_enable(WORD cardno, IOC0640_OPERATE funcIntHandler, PVOID operate_data);
IOC0640_API DWORD __stdcall ioc_int_disable(WORD cardno);

IOC0640_API DWORD __stdcall ioc_config_intbitmode(WORD cardno, WORD bitno,WORD enable,WORD logic);
IOC0640_API DWORD __stdcall ioc_read_intbitmode(WORD cardno, WORD bitno,WORD *enable,WORD *logic);
IOC0640_API int __stdcall ioc_read_intbitstatus(WORD cardno, WORD bitno);

IOC0640_API DWORD __stdcall ioc_config_intporten(WORD cardno,WORD m_PortNo, DWORD port_en);
IOC0640_API DWORD __stdcall ioc_config_intportlogic(WORD cardno,WORD m_PortNo, DWORD port_logic);

IOC0640_API DWORD __stdcall ioc_read_intportmode(WORD cardno, WORD m_PortNo,DWORD *enable,DWORD *logic);
IOC0640_API long __stdcall ioc_read_intportstatus(WORD cardno,WORD m_PortNo);

IOC0640_API DWORD __stdcall ioc_set_filter(WORD cardno, double filter);



#ifdef __cplusplus
}
#endif

#endif 