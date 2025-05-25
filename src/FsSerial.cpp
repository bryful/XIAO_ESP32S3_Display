#include "FsSerial.hpp"
bool BrySerial::CreateHeader(byte *head, String header, uint32_t size)
  {
    if (header.length() < 4)
      return false;
    head[0] = 't';
    head[1] = 'e';
    head[2] = 'x';
    head[3] = 't';
    head[4] = head[5] = head[6] = head[7] = '\0';
    for (int i = 0; i < 4; ++i)
    {
      head[i] = (byte)(header[i]);
      head[i + 4] = (byte)((size >> (i * 8)) & 0xFF);
    }
    return true;
  }
  void BrySerial::SendText(String str)
  {
    if (str.length() <= 0)
      return;
    byte head[8];
    if (CreateHeader(head, "text", str.length()) == false)
      return;
    Serial.write((const char *)head, 8);
    Serial.write(str.c_str(), str.length());
    Serial.flush();
  }
  void BrySerial::SendBin(String key, uint8_t *data, uint32_t size)
  {
    byte head[8];
    if (CreateHeader(head, key, size) == false)
      return;

    Serial.write((const char *)head, 8);
    Serial.write(data, size);
    Serial.flush();
  }
  bool BrySerial::compHeader(char *head, char *header)
  {
    if (strlen(header) < 4)
      return false;
    if (head[0] != header[0])
      return false;
    if (head[1] != header[1])
      return false;
    if (head[2] != header[2])
      return false;
    if (head[3] != header[3])
      return false;
    return true;
  }