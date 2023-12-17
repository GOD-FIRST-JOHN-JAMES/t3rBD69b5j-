THANK YOU JESUS CHRIST MY LORD


require "rbnacl"
require "base64"

key = Base64.decode64("YOUR_BASE64_KEY")
public_key = RbNaCl::PublicKey.new(key)

box = RbNaCl::Boxes::Sealed.from_public_key(public_key)
encrypted_secret = box.encrypt("YOUR_SECRET")

# Print the base64 encoded secret
puts Base64.strict_encode64(encrypted_secret)
var secretValue = System.Text.Encoding.UTF8.GetBytes("YOUR_SECRET");
var publicKey = Convert.FromBase64String("YOUR_BASE64_KEY");

var sealedPublicKeyBox = Sodium.SealedPublicKeyBox.Create(secretValue, publicKey);

Console.WriteLine(Convert.ToBase64String(sealedPublicKeyBox));
from base64 import b64encode
from nacl import encoding, public

def encrypt(public_key: str, secret_value: str) -> str:
  """Encrypt a Unicode string using the public key."""
  public_key = public.PublicKey(public_key.encode("utf-8"), encoding.Base64Encoder())
  sealed_box = public.SealedBox(public_key)
  encrypted = sealed_box.encrypt(secret_value.encode("utf-8"))
  return b64encode(encrypted).decode("utf-8")

encrypt("YOUR_BASE64_KEY", "YOUR_SECRET")
const sodium = require('libsodium-wrappers')

const secret = 'YOUR_SECRET'
const key = 'YOUR_BASE64_KEY'

//Check if libsodium is ready and then proceed.
sodium.ready.then(() => {
  // Convert the secret and key to a Uint8Array.
  let binkey = sodium.from_base64(key, sodium.base64_variants.ORIGINAL)
  let binsec = sodium.from_string(secret)

  // Encrypt the secret using libsodium
  let encBytes = sodium.crypto_box_seal(binsec, binkey)

  // Convert the encrypted Uint8Array to Base64
  let output = sodium.to_base64(encBytes, sodium.base64_variants.ORIGINAL)

  // Print the output
  console.log(output)
});
Client: To Do Android; Version: 2.109.8580.00.betabuild#: 0;UserId: e4d0ed1b31d50fee; SessionId: a54ab79f-7e77-4310-80fa-e179574e41fc; DeviceId: 2e83ca9200153cbb