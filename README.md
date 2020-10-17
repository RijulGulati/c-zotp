# libzotp
ZOTP is a simple CLI tool to generate TOTP codes.

# Pre-requisits
- gcc
- Requires [libzotp](https://gitlab.com/GRijul/libzotp) installed. 

# Features
- Supports [andOTP](https://github.com/andOTP/andOTP) JSON file format (encrypted/decrypted).

# Limitations
- This tool (for now) is limited to andOTP-specific JSON file to provide OTP codes. 
- Cannot add/remove records (see next section).

## What's planned
ZOTP is still in development phase. I have the following items planned for immediate future. If you require some feature, please create an issue for the same.

- Add/Remove entry.
- Filter record(s).

#### Things I have in mind
- Add GUI: This is in my TODO. I haven't decided yet how this should be implemented. If you want to work on this, feel free to do so. Just create an issue so we can keep a track about the same.


## Installation
(This will install zotp binary in ````/usr/local/bin```` directory. Please make sure env. variable ````$LD_LIBRARY_PATH```` recognizes path ````/usr/local/lib```` (where libzotp is installed))
````
$ make && sudo make install
````

## Usage
- For now, zotp can show OTP using encrypted/decrypted andOTP JSON file.
- Use ````--help```` to display help.
- Use ````--encrypted-file <file> OR --decrypted-file <file>```` to use encrypted/decrypted file.

#### Example
````
$ zotp --encrypted-file otp_accounts.json.aes

(Enter password on prompt)
````

# Licence
[MIT](https://gitlab.com/GRijul/zotp/-/blob/master/LICENCE)
