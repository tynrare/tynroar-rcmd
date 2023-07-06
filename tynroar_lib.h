bool isAnyKeyPressed(int count, ...)
{
  bool pressed = false;

  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++)
  {
    if (IsKeyDown(va_arg(args, int)))
    {
      pressed = true;
    }
  }

  va_end(args);

  return pressed;
}