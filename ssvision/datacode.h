#ifndef DATACODE_H
#define DATACODE_H


namespace ssvision
{
    /*
      "Aztec Code", "Data Matrix ECC 200", "GS1 Aztec Code", "GS1 DataMatrix", "GS1 QR Code", "Micro QR Code", "PDF417", "QR Code"
    */
    extern const char* const k2DCodeDataMatrixECC200;  // "Data Matrix ECC 200"

    /**
    @param code_name
    "2/5 Industrial",      "2/5 Interleaved",
    "Codabar",
    "Code 128",      "Code 39",       "Code 93",
    "EAN-13 Add-On 2",      "EAN-13 Add-On 5",        "EAN-13",          "EAN-8 Add-On 2",      "EAN-8 Add-On 5",      "EAN-8",

    "GS1 DataBar Expanded Stacked",    "GS1 DataBar Expanded",    "GS1 DataBar Limited",    "GS1 DataBar Omnidir",
    "GS1 DataBar Stacked Omnidir",     "GS1 DataBar Stacked",     "GS1 DataBar Truncated",  "GS1-128",

    "MSI",
    "PharmaCode",
    "UPC-A Add-On 2",  "UPC-A Add-On 5",   "UPC-A",   "UPC-E Add-On 2",   "UPC-E Add-On 5",   "UPC-E",
    "auto"
    */
    extern const char* const kBarCodeCode128;  // "Code 128"
}

#endif // DATACODE_H
