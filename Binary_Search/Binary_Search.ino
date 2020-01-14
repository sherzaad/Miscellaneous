//returns elements between which value lies (in case of sorted array - no repeating values)
#define SIZE 255

const uint16_t sample_arr[SIZE] = {2, 4, 5, 7, 12, 18, 27, 31, 35, 41, 45, 46, 48, 52, 53, 54, 63, 71, 74, 76, 83, 84, 85, 87, 95, 96, 97, 98, 100, 103, 106, 108, 109, 110, 115, 118, 120, 123, 124, 127, 129, 135, 139, 141, 144, 146, 147, 150, 152, 160, 161, 167, 171, 172, 174, 176, 179, 180, 181, 183, 184, 188, 195, 198, 201, 202, 203, 204, 205, 212, 213, 214, 215, 217, 221, 222, 225, 228, 229, 230, 232, 233, 236, 237, 238, 239, 243, 244, 245, 248, 250, 253, 255, 257, 258, 259, 263, 265, 266, 267, 268, 274, 277, 279, 280, 283, 284, 288, 289, 291, 292, 300, 301, 303, 304, 305, 313, 314, 315, 317, 319, 322, 323, 326, 330, 334, 339, 341, 344, 345, 349, 350, 353, 358, 359, 360, 362, 363, 366, 369, 372, 374, 377, 381, 382, 383, 385, 388, 389, 391, 395, 396, 399, 401, 403, 404, 405, 407, 408, 419, 420, 421, 422, 423, 428, 429, 431, 434, 435, 436, 437, 438, 441, 445, 446, 449, 451, 455, 459, 460, 461, 463, 468, 472, 475, 478, 479, 484, 486, 488, 489, 493, 499, 502, 506, 509, 513, 515, 517, 518, 523, 524, 529, 534, 539, 540, 543, 544, 548, 550, 554, 557, 559, 560, 561, 562, 565, 567, 573, 574, 575, 577, 579, 580, 582, 587, 589, 592, 597, 602, 606, 607, 608, 609, 617, 620, 621, 623, 624, 625, 627, 628, 629, 630, 635, 638, 639, 641, 643, 644, 646, 647, 649, 650, 654};

uint8_t  BinarySearch(uint16_t *arr, uint8_t size, uint16_t value, uint16_t *result) {
  uint8_t  mid, low = 0, high = size - 1;

  if (value > *(arr + size - 1) || value < *arr) {
    return 0; //out of range value
  }

  while (low <= high) {
    mid = (low + high) / 2;

    if (*(arr + mid) > value) {
      high = mid - 1;
    }
    else if (*(arr + mid) < value) {
      low = mid + 1;
    }
    else {
      *result = *(arr + mid);
      return 1; //exact value found
    }

  }

  *result = *(arr + high);
  *(result + 1) = *(arr + high + 1);
  return 2; //value between 2 possible results
}

void setup() {
  uint16_t  result[2];
  uint16_t val = 700;

  Serial.begin(115200);

  unsigned long oldtime = micros();
  uint16_t y = BinarySearch(sample_arr, SIZE, val, result);
  oldtime = micros() - oldtime;

  Serial.print("search time: ");
  Serial.println(oldtime);
  Serial.print("result: ");
  if (y > 0) {
    for (uint8_t i = 0; i < y; ++i) {
      Serial.print(result[i]);
      Serial.println(", ");
    }
  }
  else {
    Serial.println("value out if range!");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
