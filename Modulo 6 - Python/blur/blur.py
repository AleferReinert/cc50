from PIL import Image, ImageFilter

before = Image.open("images/yard.bmp")
after = before.filter(ImageFilter.BoxBlur(1.5))
after.save("images/yard_blur.bmp")