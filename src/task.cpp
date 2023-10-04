#include "task.h"


static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

void FastLEDshowESP32()
{
  if (userTaskHandle == 0)
  {
    // -- Store the handle of the current task, so that the show task can
    //    notify it when it's done
    userTaskHandle = xTaskGetCurrentTaskHandle();

    // -- Trigger the show task
    xTaskNotifyGive(FastLEDshowTaskHandle);

    // -- Wait to be notified that it's done
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200);
    ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
    userTaskHandle = 0;
  }
}

void FastLEDshowTask(void *pvParameters)
{
  // -- Run forever...
  for (;;)
  {
    // -- Wait for the trigger
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // -- Do the show (synchronously)
    FastLED.show();

    // -- Notify the calling task
    xTaskNotifyGive(userTaskHandle);
  }
}

void createShowTask()
{
    Serial.print("FastLed will run on core ");
    Serial.println(FASTLED_SHOW_CORE);
    xTaskCreatePinnedToCore(
        FastLEDshowTask,
        "FastLEDshowTask",
        2048,
        NULL,
        2,
        &FastLEDshowTaskHandle,
        FASTLED_SHOW_CORE
    );
}