#include "adc.h"
#include "stm32f10x.h"
void config_adc(uint16_t *data)
{
	//config RCC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	//CONFIG GPIO
	GPIO_InitTypeDef GPIO_STRUCT;
	GPIO_STRUCT.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_STRUCT.GPIO_Pin=GPIO_Pin_1;
	GPIO_STRUCT.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_STRUCT);
	GPIO_STRUCT.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_STRUCT);

	//CONFIG ADC
	ADC_InitTypeDef ADC_STRUCT;
	ADC_STRUCT.ADC_ContinuousConvMode=ENABLE; //tắt chế độ quét tự động
	ADC_STRUCT.ADC_Mode=ADC_Mode_Independent;
	ADC_STRUCT.ADC_ScanConvMode=ENABLE; //quet lan luot cac kenh
	ADC_STRUCT.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//Chọn sự kiện bên ngoài được sử dụng để kích hoạt bắt đầu chuyển đổi của một nhóm thông thường
	ADC_STRUCT.ADC_DataAlign=ADC_DataAlign_Left; //vi du liu la 12 nit luu o thanh 32 bit =>can le cho du lieu
	ADC_STRUCT.ADC_NbrOfChannel=2;//số lượng chuyển đổi ADC sẽ được thực hiện bằng cách sử dụng bộ tuần tự cho nhóm kênh thông thường.(1-16)
	ADC_Init(ADC1, &ADC_STRUCT);

	//CAU HINH CHANEL RANK (CHANGE 8 9 TUONG UNG VOI PB0 PB1(DOC CAU HINH TUNG CHAN DATASHEET))
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_7Cycles5);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1); //RESET THANH GHI HIỆU CHỈNH CỦA ADC1
   while (ADC_GetResetCalibrationStatus(ADC1)){} //CHO RESET XONG (CO SE RESET LEN 1)
   ADC_StartCalibration(ADC1);//KHOI DONG BO CALIB
   while(ADC_GetCalibrationStatus(ADC1));//CHO BAT BO HIEU CHINH XONG


   //KHI chuyên doi nhieu kenh thi can lay gia tri o thanh ghi luu gia tri cua adc1 luu vao bọ DMA
   //vi adc1 chi co 1 thanh de ghi gia tri vi vay moi lan quat 1 kenh no sẽ ghi vao thnah dáy ,xong den lan quet 2 la kenh khac thi no sẽ de len gia tri truoc


   //khoi tao bo DMA

   //BAT CLOCK CHO DMA1
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
   DMA_InitTypeDef DMA_STRUCT;
   //dua gia tricua kenh 1 DMA1 ve mac dinh
   DMA_DeInit(DMA1_Channel1);
   DMA_STRUCT.DMA_BufferSize=2;//DMA_BufferSize : Kích thước của mảng dữ liệu.
   DMA_STRUCT.DMA_DIR=DMA_DIR_PeripheralSRC;  //Chỉ định xem dữ liệu sẽ được chuyển từ bộ nhớ sang thiết bị ngoại vi, từ bộ nhớ sang bộ nhớ hoặc từ thiết bị ngoại vi sang bộ nhớ. Tham số này có thể là giá trị của DMA_data_transfer_direction
                                               //DMA_DIR_PeripheralSRC :chiều dữ liệu được truyền là từ ngoại vi.
   DMA_STRUCT.DMA_MemoryBaseAddr=(uint32_t)data; //noi luu gia tri
   DMA_STRUCT.DMA_PeripheralBaseAddr=(uint32_t)(ADC1->DR);//dia chi adc1
   DMA_STRUCT.DMA_M2M=DMA_M2M_Disable; // Kênh DMA cũng có thể được kích hoạt mà không cần request từ ngoại vi, chế độ này được gọi là memory to memory mode.
   DMA_STRUCT.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
   DMA_STRUCT.DMA_MemoryInc=DMA_MemoryInc_Enable;//Chỉ định liệu thanh ghi địa chỉ bộ nhớ có được tăng lên hay không.:ENABLE VI DOC 2 KENH
   DMA_STRUCT.DMA_Mode=DMA_Mode_Circular;
   DMA_STRUCT.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
   DMA_STRUCT.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//đối với chuyển đổi ngoại vi nên tắt ,vì tăng không cần thiết ,có thể gây nguy hiểm
                                                        //Chỉ định liệu thanh ghi địa chỉ ngoại vi có nên được tăng lên hay không
   DMA_STRUCT.DMA_Priority=DMA_Priority_High;//chi dinh muc do uu tien ,có 4 muwacs giũa cac dma
   //khoi dogn cau hinh
   DMA_Init(DMA1_Channel1, &DMA_STRUCT);
   //BAT NGAT KHI DMA NHAN DU DU LIEU
   DMA_ITConfig(DMA1_Channel1, DMA_IT_TC,ENABLE);
   DMA_Cmd(DMA1_Channel1, ENABLE);
//BAT ADC VOI DMA
   ADC_DMACmd(ADC1, ENABLE);
   //CAU HINH UU TIEN CHO NGAT DMA1
   NVIC_InitTypeDef ADC_DMA_IRQStruct;
    ADC_DMA_IRQStruct.NVIC_IRQChannel=DMA1_Channel1_IRQn;
    ADC_DMA_IRQStruct.NVIC_IRQChannelCmd = ENABLE ;
    ADC_DMA_IRQStruct.NVIC_IRQChannelPreemptionPriority =2 ;
    ADC_DMA_IRQStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&ADC_DMA_IRQStruct);

}


void read_adc()
{
	//bat dau chuyen doi adc
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
