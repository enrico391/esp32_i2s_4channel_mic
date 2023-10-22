/*
  ESP32 I2S Microphone Sample
  esp32-i2s-mic-sample.ino
  Sample sound from I2S microphone, display on Serial Plotter
  Requires INMP441 I2S microphone
 
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
 
// Include I2S driver
#include <Arduino.h>
#include <driver/i2s.h>
 
// Connections to INMP441 I2S microphone
#define I2S_WS 25
#define I2S_SD 33
#define I2S_SCK 32

#define I2S_WS_1 26
#define I2S_SD_1 14
#define I2S_SCK_1 27
 
// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0

// Use I2S Processor 1
#define I2S_PORT_1 I2S_NUM_1
 
// Define input buffer length
#define bufferLen 64
int16_t sBuffer[bufferLen];

#define bufferLen_1 64
int16_t sBuffer_1[bufferLen_1];
 
void i2s_install() {
  // Set up I2S Processor configuration
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format =  I2S_CHANNEL_FMT_RIGHT_LEFT, //I2S_CHANNEL_FMT_ONLY_LEFT, 
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };
 
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  i2s_driver_install(I2S_PORT_1, &i2s_config, 0, NULL);
}
 
void i2s_setpin() {
  // Set I2S pin configuration
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  const i2s_pin_config_t pin_config_1 = {
    .bck_io_num = I2S_SCK_1,
    .ws_io_num = I2S_WS_1,
    .data_out_num = -1,
    .data_in_num = I2S_SD_1
  };
 
  i2s_set_pin(I2S_PORT, &pin_config);

  i2s_set_pin(I2S_PORT_1, &pin_config_1);
}
 
void setup() {
 
  // Set up Serial Monitor
  Serial.begin(115200);
  Serial.println(" ");
 
  delay(1000);
 
  // Set up I2S
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);

  i2s_start(I2S_PORT_1);
 
 
  delay(500);
}
 
void loop() {
 
  // False print statements to "lock range" on serial plotter display
  // Change rangelimit value to adjust "sensitivity"
  int rangelimit = 3000;
  Serial.print(rangelimit * -1);
  Serial.print(" ");
  Serial.print(rangelimit);
  Serial.print(" ");
 
  // Get I2S data and place in data buffer
  size_t bytesIn = 0;

  size_t bytesIn_1 = 0;

  
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);
  
  esp_err_t result_1 = i2s_read(I2S_PORT_1, &sBuffer_1, bufferLen, &bytesIn_1, portMAX_DELAY);
  
   if (result == ESP_OK && result_1 == ESP_OK)
   {
     // Read I2S data buffer
     int16_t samples_read = bytesIn /8 ;///8; //8 

     int16_t samples_read_1 = bytesIn_1 /8 ;///8; //8 

     if (samples_read > 0 && samples_read_1 > 0) {
       float mean_right = 0;
       float mean_left = 0;

       float mean_right_1 = 0;
       float mean_left_1 = 0;


       for (int16_t i = 0; i < samples_read; ++i) {
        //seguence bytes | 0 LEFT | | 1 RIGHT | | 2 LEFT | | 3 RIGHT | | 4 LEFT | | 5 RIGHT | | 6 LEFT | | 7 RIGHT |
        if(i % 2 == 0){
          mean_left += (sBuffer[i]);

          mean_left_1 += (sBuffer_1[i]);
        }
        else{
          mean_right += (sBuffer[i]); //sBuffer contains 64 bit
          mean_right_1 += (sBuffer_1[i]);
        }
       }
       // Average the data reading
       mean_right /= ((samples_read/2));
       mean_left /= (samples_read/2);

       mean_right_1 /= ((samples_read/2));
       mean_left_1 /= (samples_read/2);

       // Print to serial plotter
       Serial.print(mean_right);
       Serial.print(" ");
       Serial.print(mean_left);
       Serial.print(" ");
       Serial.print(mean_right_1);
       Serial.print(" ");
       Serial.print(mean_left_1);
       Serial.println(" ");
     }
   }

}



/*
// Read I2S data buffer
     int16_t samples_read = bytesIn /8 ;///8; //8 
     if (samples_read > 0) {
       float mean_right = 0;
       float mean_left = 0;
       for (int16_t i = 0; i < samples_read; ++i) {
        //seguence bytes | 0 LEFT | | 1 RIGHT | | 2 LEFT | | 3 RIGHT | | 4 LEFT | | 5 RIGHT | | 6 LEFT | | 7 RIGHT |
        if(i % 2 == 0){
          mean_left += (sBuffer[i]);
        }
        else{
          mean_right += (sBuffer[i]); //sBuffer contains 64 bit
        }
       }
       // Average the data reading
       mean_right /= ((samples_read/2));
       mean_left /= (samples_read/2);
       // Print to serial plotter
       Serial.print(mean_right);
       Serial.print(" ");
       Serial.print(mean_left);
       Serial.print(" ");
       Serial.println(samples_read);
     }

*/