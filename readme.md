# QR Code recorder

Designed to work with [VENREA QR 2D Barcode Scanner](https://www.amazon.com/gp/product/B09MS66V9B?ref=ppx_pt2_dt_b_prod_image) [**Model: VENREA-C2000-2D**].

## Set up repo

`cmake -S . -B artifacts/obj`

## Build repo

`cmake --build artifacts/obj --config Release --target install`

## Run application

`./artifacts/bin/qrcode_recorder`

Using a QR code reader, scan a QR code and the application
will parse the input and display and record only the email.
The application will create a text file with one line per
email.