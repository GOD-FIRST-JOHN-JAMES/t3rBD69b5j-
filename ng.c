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
});%PDF-1.5
%����

1 0 obj
<</Type /Catalog
/Pages 2 0 R
/Outlines 78 0 R
/Lang (en)>>
endobj

79 0 obj
<</Length 133 0 R
/Filter /FlateDecode
/Type /ObjStm
/N 54
/First 454>>
stream
x��ZK��8��W�1$h��H*�Ⱥ�g���f؃,�mMԢ��{<�~�(�&-K����a[��]_U��"�V��j�E�e���J�2I�1�k	�8Ze)(�d�Z),J��~f��,Y�(��>!e��Y�[U�t$�L����Gǅx�hG
\0zY���$���HA�$�'�8�ӕJ )naʊC�3�{�ۥ�4��K��~I!�bz" e�Xe�&����1mQ�JFdpEEH�G�fL�	"�'J�`_�D*h�H�/	��c<EH����H��+�v�W�L#��3�͎��T	}���¥��b	���b�O)Pd��i���[f��Ç��ˮ���K�����3����QW���>7��.ۼ+M����p0/�����jݴ��о,�.ʼ��.�����r��f�WD��4����ݗ���(H?���u���b�w��?�K����������Cuh��GO⵩;$����-�z�f����D�K����a���O����)�\�y��iRH?�fW�;xΛo�k/�2#���`����n��+4�N���.�y��g,0&�Y��W.�*���'�楆]Z���le����4�zVG:-�<�/C<��a�R(DY��Y��1�>�sI&\��s����6O?�Ǿ%c�~:��c��ȓ	��	;]�k���4�O���/��������Ƕo�d�Ow�n�B4������Q��sCK���O�~˫�A��w��|hI��԰P�m���f�
�Q�WRW���O]?��s�c��[c������Vwk��@#��Z�Ͷ�`���9O���[\>"�m��ѵ��9����(�����J����Ģ�hB@�ۼ�:l}�>����k0ī8�rSC���<3Qq��9u��j�F��o�0�_�U.;�5���vǦ����|z�$���K�˕rM��|S>�%,�R���#)�tPvf��8[�%��cP�&��ha��Fvy�J��9Q�������1��4�|V�lAꩥ���%{���IF���r> �\���Q^�8�����O���y��	��^W�n{�!�K�su��^��P�{�6��@%6H����5������=[EB�_E<�"l�"��#�gbM�y��]O�s)�~|.����̽��ĸ��H�Mް������W�O�,�Hoϙփ�!s�f#Ϗg�Rk�w`|�e�F�:��7�5��УWKS�����w𩆞P��֕a[���V���o���	��D�~6$AO*���W��r2x�FB:��Ӑ��̽_Eͽۻ�����ߩ'��y�x�;~�Hs�3�(�KdX��罞.`NXY�X9N�/nc��	!�u�LLӉ�����b�r絵G�q�u���.�"��9Bҋ�y�֙,�QXOM2�M�B�%�K�tkhm���)op�\.I@<
�$�K/e�f�.��P�h���k�{�J]%?�Z9��S�x��W�>.N<�*�5W��g�9��Y�C�jl6:@���.[�l7Z��T�4�d�����oG�ϟ|�e���ʪ!ؤ��h%]�2q�sG��Ƽ����?C	��*7'��x{�\o��ܜԬ[�\�5��v��N?�+~�8k�x�X��i�7��j�.w60x�8\P�4%F�3�n7t�炶/C ���.��M���Ȝ�g�+L���<�]����J���!_\j;7�b-���}��CZs%c?tc!�a:�\
�p	 ������5��~+[��p���"!͎����Uf��\@�"b�l�8�i�xQ�ڹ����B�j�hmWv� u����?r%��\_���.�_�Ɇ�� ԗa㪶E��d�?.�V�KȜ�Ć�|X,Yajt����C����jT�`H�Q�U�S8+�>��4�1���:�Sem.�-Ce:aG��a뵒��+���Kj���YM�� �z|/a�pd�Лc�U����»�:5��b��B�˂c>=&��4ߨ84f��vA�g� ��zp�j@� ^��]� ����G�w�[���:�v,�9�[��Fys���W��}���î��n���˲ɱC���\9柫��
F����������!L�,��ʟ��Ҋ� 	�c����X�R�|���_>=��>6��p���,�*��z�Y��F)7��}�S�æ�<���Wtw�g9��;��������|�;1�2[{�6�<8�Od�R��]�ڌ�p����:<��h
X!����r�T�p����zw���t�;McXg^�f���5w�RC��"�O�J�:Z�I����_��0I�۵����	�lx�yK��p�w��ݹ�������o�x`uq���ɴ
Y9��a8go̯����M_m��9O��[k�I����|�;�.vd[8��A�o��}Y��p�p�V��Р/T�7Dލ�E�X�	Hk^y��4�%E<=z�7������s���f��eo�CR�[A�#]iA�v�!��x:�Z���ap$��[��r[C���~η���u},ci-(� 17���2�i,���Q�z�D�+w�ɷ�0n2&P��x�������29Mٖ��KB(rL��g�>�d!�}���x3��G�EC�¥)�n��}�u;����G�CJ-� ��
endstream
endobj

133 0 obj
2661
endobj

2 0 obj
<</Type /Pages
/Kids [3 0 R 4 0 R 5 0 R 6 0 R 7 0 R 8 0 R 9 0 R 10 0 R 11 0 R 12 0 R 13 0 R 14 0 R 15 0 R 16 0 R 17 0 R 18 0 R 19 0 R 20 0 R 21 0 R 22 0 R 23 0 R 24 0 R 25 0 R 26 0 R 27 0 R 28 0 R 29 0 R 30 0 R 31 0 R 32 0 R 33 0 R 34 0 R 35 0 R 36 0 R 37 0 R 38 0 R 39 0 R 40 0 R 41 0 R 42 0 R 43 0 R 44 0 R 45 0 R 46 0 R 47 0 R 48 0 R 49 0 R 50 0 R 51 0 R 52 0 R 53 0 R 54 0 R 55 0 R 56 0 R 57 0 R 58 0 R 59 0 R 60 0 R 61 0 R 62 0 R 63 0 R 64 0 R 65 0 R 66 0 R 67 0 R 68 0 R 69 0 R 70 0 R 71 0 R 72 0 R 73 0 R 74 0 R 75 0 R 76 0 R 77 0 R]
/Count 75>>
endobj

134 0 obj
<</Length 135 0 R
/Filter /FlateDecode>>
stream
x��\يd7}�_Q���/`z���)��!���<����HWqNH�e0e�C�Nj�=BK��an��� %�[)�<�o.�����ǿ�9~;���_�ᗯ�wO?؇��;����������o��������������,��9~<�?v���c�5�Byx�6��m(�f��O?�}r��\h����{���<<����窭���k��w���ނ/y�����n&�����12��3m���1����t�t������`?�G[Ϯ֤��>��؏��`ߏN6ެ	+�m1_M�;3��1��mX�i��wm�/'�ѥ�}n���DY�]��l?ُ.�w���ƚ�R�-#bxl�>��C���X�{���FVn��P��������n>�UO�l���D���'v��f�����n)�a?.�����m���!�O����x�\C���>t���\l�?��fM���o�yl�ES�yB������k���ܩ�5�f&!6��c�A�ۨ��Ќ�FA�_�PD=��Gݺ6s��Q����s�F]H>��['_�_�0܉w���#�ҩ�r���y��cH�㳑�?r_�w�gX��r��Gn��6�G�nr�%���HPk42���pk�X�~�2���z�>y�dMk^�m�‚��>!���'4%!	�ƀ��u,�ڧDb�.cD\U8F���,!������:о�8	�2[x��[�o�0�(DەY�Mo4&km���nL+b6��݆���b1Cw����8��O��*�PQ�Vy��&Cg/��dD��0=�Sg(�#=��9���2%�ݜ�@��B(h,dA�� �H�D�WLڦ�C����x�����E5ނ,D"���	�nR L���޾3 U��yFξ-�s��r�إ=̚u���y��X��� qCn^<�Hӣ?�^��� iY��
�ǯ-�T�X���=�r@�PdP��^�̉�]�LAC1[`�Ou��4���H�A��2�[/n��U��m#��L�,��Y`"�	�(Ō�C4+9��ndh(��TFh�諍Ck��X��� �H{�0���9؎폑f\T]C^.i��^EuMZ�.WU��a���wyr�>W�qҋ��UDb�Y�5<!�֢z�h��K�j�����!���޴!A8�4�(��*�w�u�U+w\�"��0�+��!����j� ���Ğ'�<�}k.r�L��E��ektx̕�KF!�\/AK�t=��+�]�63��wlf���(�����0��k�P=�q}(��M-YԤ�	�E�"V�<��P��z�P�,H,Yc�`񪁀5-Ja���the��!���ZI⡠�e��Е$�,�"w�
[
�#�Y����:I���M(`I&,�&��{amd�[!���
b'���D�Jee��Q�ƒ�)�+�2a۵B�Iʐ��%<W8�D�#DK���
����=i�#���"������*�n���u��Ⱥ�Tw���+K�V+�u I�bG{�X��n|_J:W���i�"�vZŊ.�<H�p���^3�f��H�Ϊ��E��EP���hB%{~A���ދ��v�DV��YU��A�q���"�F���#�3,�H%�DE��˥蚌���9K)	(�h�]��fᔱު���.�m-6��R"Y+���Ψڽ.G�T��B|�кA�נl�of)�^�B��!����;	���8Ƈ,��(M���^�P�UN&��y�<�s��7�խטz�)!��W}��┥���$4����1�UI2�cG��0[�*![�7&���HD���G�E� r�gX�d�X��>���4�I��|N���Ԍ��A�JDh/(�랐���^��K��8qZ�Yh��J����,5g.�t����r+�����<���2c�i��k����6��e��&DӀbH�	g��t�A�x���K-q寯W��s_N��ʳ�+s���z¡�Mgf:��4�p���WM;'�u�6��8�5u{�<d-.�Ԫtv���xf߯�{V�Z1 B}����9_��b76�r[���=	Pc@�#�'�L�����g��y$�9H�Q�d��@Փً�O���g5(�pN"�B<�48l���a��V��� gA��Je:Wѫ9h����y�+O��������i�áZ�(T���ˬ	X	3�Y����>6s� ի� ���
�.KM��z	ɕg��[*�gr;�&Ȗg2BPwHk���_+�G�f3,/p�*����B��J�р�S��2+�+��&Z-Pa4���t+�X;� ����-9<X�30ο����'���
�IW�eYj�H��KHF��rS����4���2��M���m��E�TS ���(�<AB���_Ŧ��s�6�0*��S!�\^�l�E����LD������)+���,m�y�+��~ǃ���f�B��
�x�fF1^	���H�Z��2�5�z�2�[`�Ħ���͌Ύ��AϬ�~1����Л����I('y33#vC�fF1��X��I�Zżyä	��\�����B��"3T2랣��9S�׭�B�b�wJ����/b��˸ L'%��-�5�rZK��	B��rR�ܒ-O�Je��������0sV��O�J��^䟝���9��rI�Ħ�C����-xZA��
��FCK[��-- ����OI�M]����3��<W*��4�\�vF��>V��$e��$���ħ;���vJ�:�"ꩊY�72i]O�0�*�R�1Ӆ�>.���n��.D�N��:��~�ӄ���\���u��47�g�i6�Q:A3u]כ�I{��E@Y��4O+���E����V���r�i��T��R.���{>�k�؜b��umBI���<�0��bu���c�8(��< }>$���U2=�6v�|�� �9іГ���`�L���;r��=�6�<�8
��(�{��l��x��EX3��Pw�ұ_�NiY�[��S��7�2U"K�}ɱG���1'=�y&���P8��Onұc�N��Vo5��/Dy1�����yg�Y����w�VD�"Y8dX��qCD�tj�9�'��m��Y�o�&��"|����+��;008!ª_�4��  d�p���Jb��ț%pNJ�
|� OM#��xGZw��E� �oa�gĳL�׾d���rۨ��<_*��Ц���ZxO(x���fE"�Yx�p KV�-�U4���/�O�J�
�9�p�� ���W�U�������[;r��	�s����fkJR*�$��Z|�~��Ҽ��|�=\�o;%��y���R��5:�GY.M���]1��.tm��'E�wE
27H� 0r��_ߪ��:���BNLYd��n�6M�"���dd	V������'������^Hܘ��-F���'���ۘr��R�ajX�Ѣ�5_�-����+�9��!mc��>W��9
���v[/E)����a�i5m9 sZ���[r��ț%"����-�`/!�&ߣZM�x�*�Df͟�ȷ|��r�����. ��v%pc`������a�_�����o���Mz�jC�$
�� d� ��A /{n���ʤ�,�7&�3�����j��lIM��[:���d4��DH�Jps��%������o�q ���;�;	bj��fZ~�Z�ܞL��0�-�Ga.kxENB(��3��5���DNX
�y� �ޓ33#����[�*��ѝ�g�p:1Y�J���~�@��r"(\x�$�n|�����U�B�QvV5ړ�@Q�!s�U�!���j,ls"���ǝ����u��a����(��P$W��Cb4BL@��s[� ��v��l|�Y�QB��:�U�ѯ�F[�@D�����&����}����DD��mTn|L�t�vs0���sɮƀ[3.�î�¶J��\��Iy��PsInE�3L�I�� x|�*����#�	���}s���0;;�	6+�����{G
�oL�����y;#i%�D��H"IRn���������X� �y����p-�g��׵��y�x�+=�
endstream
endobj

135 0 obj
4111
endobj

137 0 obj
<</Length 138 0 R
/Filter /FlateDecode
/N 3>>
stream
x��Vy<�k~���}�͐�طF�0Ⱦ��N�13�`̠�&�p"I�9:tZ��"-ڎҦ������"�����}���]����{���~��~�x/ �c ���H��ƈ��f��E��؜�4���Ǉso��������wa-�n_���Վ��?B�����<P�6=�](�ǆ���> 
7���(A��1�iL�1��>��H�;�%(׋MJ���T��^��?�x�i�)�bzI:��Y"i.Yz:'M(�y(��$���Y�/��Z��z��X���0-���d6'���a'K��ې~�9�w Y�����0sN�H7, Y@*@�#���8 �	�@ Q`5���� �- ��T�Z� A8��Yp\7��  	����!�CT��@Z�>d
YB,�	�B�P�CH�@[�B����F�W�t��A��!hz}���a� ^�`W��W��p:�΃w�p=|n�/�7��~O" !#J�6�DX�;�D#q�و �H=҂t"=�=D��F>cp��ab0>�0��و)�Ta�b�0�1�0C�	�w,��5��c}���xl6[�=�=���}��~��pJ8C�-��Kĭ����Zq]�>�0n�ǫ�M��@</���+����w�#�O2A�`I�"D�\B9��p�p�0J�&�����@"���XLl voG��$y�!ɑJJ$m!U�ZHWH���d2Y�lG^N�7�+�����C���	ŝ��"���tQS�S�T�5�*��6R/Q�Q?��d�d|e�2�d�e�d�ʼ�%��˺ʮ�]'[.{R���k9�����[n�\���~�Iy���|�|�|�|��u�1�����W!O��%�aBӥ��8�����G7�����_��	E�Ŋ�يՊ�%J�����R�R��	��J_h,p]�[�sA˂���Ք]�y�ʭ����0T<U�Tv���<UŨ��.W�R=�zE��]�A��V�vB�:�n���^���-�IMo�4�J�K�5�4]45�4�k�kѴ���ZeZ�^2��dF�2cB[]�G[�]�ݫ=�c����Ӫ�T���ҍ�-��֝������k�{�O�g�'����џ204�0�n�n0f�l�k�ΰ�pЈj�l�nTot�g�2N2�o|�6�6I0�6�m
�ژ�M���-�.�[(XX���Ia�23���!3%��f�f�fo�-�^�{QϢ�������
~���,M,9�Ֆ���V^V��:��.6]�[|`�#k�u��v�n�o6�6B��q[=���~��*b]��ڹ�m�;k����^d��o�C�C����%�%K�uَu�'�S��A'���3۹�������˨��k��1�7n�nB��nS���ܻ<o��^O�0�*�g^:^�^�^���뽻|�>�>�}�}5|9���~�~�.�S�C����/5Y*\� ��	\��L��=��	|d���r�����_[����Bք4�|u-3
�u�ˆ�o����(��D.��y3J5�����>=��s��#+�W�|��pU���UW'�>�Fv{��lLDLS�Wv ��=�[;�q����p˸�<G^)o4�1�4n,�1~O�x�sBy�k�;���6�'�6q*)0�H�LrDrk
!%&�@A�$������ڗf���&I�Oߛ>!�΀2Vet�����H�M<��Y��)+<�d�|� ��Z��;׎��Z��z�z����-9C\7�m�6�n�ޤ�)o��f��G���$m�=�<�4��ֈ��yy��yokΗ���ow�^�����w���ʝ��7
���q�n�d�S�O3��v��(��J�v�}�T�t]��=me����{��^���vi�x��biEG�^eI�ת���nխ5�5;k��s��=�r��V�����A��Gu�um���p�2�ho����s�a�Å���>z�Ѷ��I���n7�[y��/�t�0[�Z�Z�����/����	��'Y'[N韪9M;]���m�hOh�tDu���;����y�7�ߎ��>[}N�\�y����3�]��J�z}1��p���K���_^~�����kW��^�q��p���������`�h�is����ӿ[�~�צ�����;vw:������|��=�{W��޿�`ك��a���<�>{�����'����O垖?SV����ɹ!��[�C�s�_����ב���Z��c�cgǽ��\�r�Uګ�����U���ͩ�]��591�V�v�]�{��G>,��=4��c��驂O*��~f}���et:�+�k�7�o����Τ����M�P[�%�8�8YĐ���T������L�����|Jl% �� P~2���{���Y@����!J�B��y-� �$��d��g5��P�s`��xB� �j8���ģ�p�"~���0�kL����|��Y�������VȏO1|"�P��v�N��:Bi��B_���ainn@F���l)��zg�33� ���xff�nf�:d �.� 
?��
endstream
endobj

138 0 obj
2577
endobj

139 0 obj
<</Length 141 0 R
/Filter /FlateDecode
/Type /XObject
/Subtype /Form
/FormType 1
/Resources 140 0 R
/BBox [0 580.3195 349.7988 595.2756]
/Group <</Type /Group
/S /Transparency
/I true>>>>
stream
x�E�=�0E��+���- e���j7���i��^�v�=R��T��r�Ѣ��#e�*�fs��h�4Z$lC����o[�'���=:���c�x��Ѯ;����%��1�u��������F���}p�>`�t���\-�
endstream
endobj

141 0 obj
145
endobj

140 0 obj
<</Font <</F1 142 0 R>>>>
endobj

3 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 134 0 R
/Resources <</Font <</F2 143 0 R
/F3 144 0 R>>
/XObject <</TG1 139 0 R>>
/ProcSet [/PDF /Text]
/ExtGState <</GS1 <</ca 0.0000>>
/GS2 <</ca 1.0000>>>>
/Pattern <</Pat1 145 0 R>>
/ColorSpace <</DefaultRGB [/ICCBased 137 0 R]>>>>
/Group <</S /Transparency
/CS /DeviceRGB>>
/Annots [136 0 R]>>
endobj

136 0 obj
<</Type /Annot
/Rect [0.0000 581.4768 332.1328 595.2756]
/Border [0 0 0]
/Subtype /Link
/A <</Type /Action
/S /URI
/URI (https://perspectives.sc.com/?accessible)>>>>
endobj

146 0 obj
<</Length 147 0 R
/Filter /FlateDecode>>
stream
x���[k�0���+�\�bٖ/P���̰�^`Ў6���qB�t����B��;��	��`�B(QH{qx����P�^�Ti�8������o���|ĺ)�Ʀ.<����&���g����y7)%�)w�~��*r.wRڑmE��i�Rg`7�v0S0��D�1��<��^��Ěku^�E���_��r��/��$Q�oVA�c�d�W�����֑	Ѡgr�Hj�V/��M����ޜ��y���Ӿ;P|.�����P~�u�~�ޓ�
endstream
endobj

147 0 obj
278
endobj

149 0 obj
<</Length 151 0 R
/Filter /FlateDecode
/Type /XObject
/Subtype /Form
/FormType 1
/Resources 150 0 R
/BBox [0 580.3195 349.7988 595.2756]
/Group <</Type /Group
/S /Transparency
/I true>>>>
stream
x�E�=�0E��+���- e���j7���i��^�v�=R��T��r�Ѣ��#e�*�fs��h�4Z$lC����o[�'���=:���c�x��Ѯ;����%��1�u��������F���}p�>`�t���\-�
endstream
endobj

151 0 obj
145
endobj

150 0 obj
<</Font <</F1 142 0 R>>>>
endobj

4 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 146 0 R
/Resources <</Font <</F2 143 0 R>>
/XObject <</Fm1 152 0 R
/TG1 149 0 R>>
/ProcSet [/PDF /Text]
/ExtGState <</GS1 <</ca 0.0000>>
/GS2 <</ca 1.0000>>>>
/Pattern <</Pat2 153 0 R
/Pat4 154 0 R>>>>
/Group <</S /Transparency
/CS /DeviceRGB>>
/Annots [148 0 R]>>
endobj

148 0 obj
<</Type /Annot
/Rect [0.0000 581.4768 332.1328 595.2756]
/Border [0 0 0]
/Subtype /Link
/A <</Type /Action
/S /URI
/URI (https://perspectives.sc.com/?accessible)>>>>
endobj

155 0 obj
<</Length 156 0 R
/Filter /FlateDecode>>
stream
x��Wێ7}����Qxu���.���@?�� A�b�����h�{כ���"uDR�G��%����g���GD���s�\6Э�o�8+�����-��s�ny���G��w��+WO�d��B�/���7.1f����ֽ�¿���P�;5�e�e����x����
û��߻��3����6	Br���~�D��T3���`	N��գ#+�Z[���Hhc�q��d:�Y�+Ym��L����`AI7@J�Jr��:3�n2�1�Bn��^.U��@=js���Mhg��ݣ��k�c�̥���Qٕ�,�Z����Sk)Ai
&��n�R���u!ǉ�lT7�k#�<P�1�,�K.�쳜���p�\�@QJ����>���d*3o�V�mS^??�^m���w�!����Q�^��/mI���"I����98O����}7<��[�4\���܎��+݂�H]�bi���ԭ@^к�H�"J�� ��4rHرn�Qu�����Z[O�ы[����d��p1T2��o���Bѥ�ZgS|�U �a�4��Y�E�W�(�I���N����j�ؙ�4�tVuY���gy��t��E~�"^!�����J�j
��n{�Ѣ�핝�\`�P�Z5h�UT.�LTo���-��ȷ)��el5F��G���3�#Z�j��MY$�n��[|g�V2@#������%��U0t-��E��&#љ��0(��'#���j1��F��{��wMʜ�al���2B�f�T��T�d#T��eJ͓�꜡��E��9�]�1wd�'�2O>��kr�]�P�7�!��4����'9�JQ�M�]�7�4D����I����a�^�3*�lwg���V\@�� MJ�fʅ��y�2�	\���l���ƍXm�e���н>-˪�����~����'�/@��ſ<��Ǖ3���
endstream
endobj

156 0 obj
973
endobj

5 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 155 0 R
/Resources <</Font <</F4 164 0 R>>
/XObject <</I1 165 0 R
/I2 166 0 R
/I3 167 0 R
/I4 168 0 R>>
/ProcSet [/PDF /Text /ImageC]
/ColorSpace <</DefaultRGB [/ICCBased 137 0 R]>>>>
/Annots 163 0 R>>
endobj

169 0 obj
<</Length 170 0 R
/Filter /FlateDecode
/Type /ObjStm
/N 7
/First 53>>
stream
x����J1@�����Iڦ�eA��i��{Q��������=	2�^
i^Ҕ�@�(+�
��l�!Esdnd(I���G�A�0�f����Mn�w�M��x \��q��nx��O�Qk� \�j%P�T+H���py<='�[��������a|�����hn ��?x�-{�v������HX��;)h�啄�]KTQ�V��p& a��׌{�*+֨�ܻf��vE��oW�Xv��_z�n�~;2�i
endstream
endobj

170 0 obj
246
endobj

171 0 obj
<</Length 172 0 R
/Filter /FlateDecode>>
stream
x��V�n�@��+|FJ��^�Rf&�8#�l"������m���$!����Z߫�}ǆ"QO��>ևW6/B����>_�KoWQ������z2��զr�2^x��}|��|��$k���8��N�$��B��\�u��W�n�UB��g���s��agWI������Z����,L�u����G��۟/{�����������d{�r~���� ���u�މ7�uS�P�	Z�$~Ұ& ���%T�o�(^�3kęn��V7Eb�(���� �d�r̟�G4�m4�Лu"
��Ap��FF�,m���3I�DD�,�Ab���N���፦�QOk��7���s�#�X�({W�F(TU;�|7&j�l�J�ڠ�j�_g�n
##ܒ��R/�~���B�5T���~���C��S��ҹ�>F�{={��#�Q��0�Mi����	�l�5���)�b���W�#��`�`�*���c��$��k�̤Cn�%&Z"�1 Л|�A�Lpv3�A�ATL��h�%4�6��#����L��'6��)?��*}��b�OT�.m�� ��TE3ƴ���j�	0�L t��&4o�-����z�q�/c�/ӈv��v�d�O�Ou�f4���3Yٙ�v9��q!�a��"���_�@j��(�q��Q��ѽ���+�-'���M�:�ǂ%Ԅ��ͥc�i�F�<mF9RL�)�������P����Y]����n`3">a�*q�����
endstream
endobj

172 0 obj
755
endobj

6 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 171 0 R
/Resources <</Font <</F4 164 0 R>>
/XObject <</I5 179 0 R
/I6 180 0 R
/I7 181 0 R>>
/ProcSet [/PDF /Text /ImageC]
/ColorSpace <</DefaultRGB [/ICCBased 137 0 R]>>>>
/Annots 178 0 R>>
endobj

182 0 obj
<</Length 183 0 R
/Filter /FlateDecode
/Type /ObjStm
/N 6
/First 45>>
stream
x����N1��<����c�q��#Sa N� 7 �+j����)+j��D����j�U�Rrȵ9�uV(da�{	���YN�k�V�x��>A�����vz^``��S"C6#`�Jn�E��7��˴�!����ۏ��x��u~�z:�%iG_�x��4�1�׿iSF�Z#d!���_V��\�ٰum���|�3��.h����t�V�-e���&�M��Pl�~����
endstream
endobj

183 0 obj
229
endobj

184 0 obj
<</Length 185 0 R
/Filter /FlateDecode>>
stream
x��T�j�0}�W��P�$ے�Bw&��-��ez������g�ē�3�mB���s�#�O����#A�%�T�&��7�י{p�˟��n�_��>���G����r�����q��a?�����3wu��L�O��|o��|�{G��n�=G��~�X � )B�|�V;6�)��uk,���7��q� ���澦��B
��B,TFk�������V��Z[G�a�v�PĜ��pMt�	;�>e��I�2s!�j�-$g�r��e���s��Ȅ5eQ��(k,[9(��)�vC2$\��[��d�:f��G�(�%�w9F����2�òE�)6ђu�JA�j�V,��an�G��Ycw�g�Ȣ��粑��β�7�H\N��nh�����()�P�P\UdݗwA�v.x��y�Oo��o��3Yk$����4K�+Wj@��$;�1E��w+��D�%x%�T�� al��FW
�*�=\�m�ʋ����C���x_��/�)2�
endstream
endobj

185 0 obj
492
endobj

187 0 obj
<</Length 189 0 R
/Filter /FlateDecode
/Type /XObject
/Subtype /Form
/FormType 1
/Resources 188 0 R
/BBox [0 580.3195 349.7988 595.2756]
/Group <</Type /Group
/S /Transparency
/I true>>>>
stream
x�E�=�0E��+���- e���j7���i��^�v�=R��T��r�Ѣ��#e�*�fs��h�4Z$lC����o[�'���=:���c�x��Ѯ;����%��1�u��������F���}p�>`�t���\-�
endstream
endobj

189 0 obj
145
endobj

188 0 obj
<</Font <</F1 142 0 R>>>>
endobj

7 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 184 0 R
/Resources <</Font <</F2 143 0 R>>
/XObject <</Fm1 152 0 R
/TG1 187 0 R>>
/ProcSet [/PDF /Text]
/ExtGState <</GS1 <</ca 0.0000>>
/GS2 <</ca 1.0000>>>>
/Pattern <</Pat4 154 0 R
/Pat5 190 0 R>>>>
/Group <</S /Transparency
/CS /DeviceRGB>>
/Annots [186 0 R]>>
endobj

186 0 obj
<</Type /Annot
/Rect [0.0000 581.4768 332.1328 595.2756]
/Border [0 0 0]
/Subtype /Link
/A <</Type /Action
/S /URI
/URI (https://perspectives.sc.com/?accessible)>>>>
endobj

191 0 obj
<</Length 192 0 R
/Filter /FlateDecode>>
stream
x��Zێ�}�����,Rw``��+�[����Y�ֻ@~?�RI%���6��2�S�"���������Ř��|�G��l.y�U^0g/?��x��`���c^<�p�������ۗ��~����ӻ?����������9\~����n�_8���N�-9�(|����0����^?<������<�Y��|��n�w�!g/���n��:ևOO�t���,Yvֲ��jo�N�f����|>�ؼ�A���r��R2�=��ϘX��#�16wc���Y�<��	o^������)Nc��m^�%�鞌���d3�\˓�.)'��t�Rά��UX	FIu��0�>���s[�ݵ��bzh�'�I*�Ά(:v���=�,3��$NuD�x��9gR��B�G姫}�w���Ň\��# \.�6��oD��ч�)�ϖ�M��>�boK'~�5��|��h;SGa�����|ff���W���]��!(�����D^�U�t:w\D/�ך �۠`N��1��"�C9��,�%',��5�� �C��d�3�ݘ�k�*�Q� +��f���^�K �S��D�!�d;/Z�h7�bP��vf�Q�Z�p��+����}��m��%�)Ծn� �������)�u���.�#�����D(@��b�!.��/��k������ZNFC���C�7�V�H9��	�߃KG����Y0(���������~6r"!�0%`t y*4�	��w����Q����Rh��@�9�ϸ�(=�%���� ��6(� i��������i�0]�!L�ď����(7��%FH�!��0�/����·��YgYC�фK����"���)]n��a�q�0�!�1�æ�@�"����!Դ:�GV����Ŋ}�/[p�u� �K��WbÚ\�q�����0,u�
�^�a�g�у��&��&d�"~�ސ筽5&w��lW��d������5)�u섗��R�2�-�d�?��6�ow'�es�3�p�����u����r	Q
C����<�Kb���W�g$-���M���s��������i��Pg��@��	�L�e�����<o� �`7-5� �Xմ|d
���U�V�q�$�Éʒ
�KȽ��9�ݳ�yÑ����*h��"_�q����lن�\5�{^Aʚ�^�������\��c`%+�'X�- �e��6K8�d���,��!��U��B�}� ����[w8�/9V
��p �db�����
�f���v�:}R���#��� ���6"�+�R�46#�7���x�]�駻����W��Ţ.��K�U:=�F�4RfH1�S�ƽi���V��Ɩ�a�:QZ݂v�W}���!�n�M\��<��
�O�
X�X,j��+ąt��C8��I<'?�]���		�Ey�*���=Q�Ԋ�n<�6�d{YHLg`Ѣ+���,�F+��^J�Ð�����*,DS�IǡL��W��� Tɬes&��k�e}�:��`Ϲ*�9Û�r�֕J���y�m��=T���n��K�[� :h�f�g�3sV�B0���{"��[sɥ|tr�H+�?�M�X/;~��k_Q%� ��*��x���3���un5 ].a�1��s�5�h�KЕA�ͨ티x�9���eZ��5���ؙ�#!���+�VEٶCs ��ϕ�S�ٱ6��-�i�����זʃ�1NUW������x@�f��5�Pq��n���V!_3d�g�å��D���H���W��,q����u�ٔK)_�UE7ǫĴ�Ί�\��*�VWc��]����t���H�V|&�Y3�Y|lJTB(�>+�@r���TZ�9�>`�H*>m��J��J��Yħd��Ƴ�̻u,u;��9֧d�����k�����[��]���	��j��x�z�u׈-q�{��TڭN6�[_]�(��mw�C��f9N��ԻCJ5靷)�`�tj�|�QھR378�f���[s��@�vF:��}�9�A�����}�Qj�8J8�r<aY�����CeV'��x�*Z���=�,�8��T0���(�t���˼�T��F�Ii��C(2P,Ρ8z:��<��+z�&!G����f�s�ӌG��n�IV�D��	%�T��%������D�F���/;�������ZS=.!�r�~��L�?���n��{�Α��1��*v�=�����s-�bn�}�pNS�r�6���DC"��ѷ��H�V�@��k'�4s�v.������UM����h�?H�?u�Զ�M��ۙ��n��u�R��x곗�O�H^KB�i�h���Ƒ��i���C���+)����Ri�&Tw��F��F�с�/EB)),|��ϊ�Wi[6����o�Ƹ�< ��VC���beK2���,�zLC`��Hk���ز���b�R6r��/g9��69|�O]D#pL=�ln�����z8��V.�ZC�'�W+]�cө�B� ���gs��s�[O`ܢ8(=,<��q<�*��-��^�v�z�l�C�N�K��N�����Ԁ0�u$<�����U��OX�e���":�=`na���ݎ�t<�u����c��ҹSՁ���·�R��%\O%����rD:t��z�D$M|��Exq�D�H���UH���!
Y�w��ѩ���,��K��#��rf���m���ͦ�(��_s�֞
endstream
endobj

192 0 obj
2741
endobj

8 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 191 0 R
/Resources <</Font <</F3 144 0 R
/F5 198 0 R>>
/XObject <</I8 199 0 R>>
/ProcSet [/PDF /Text /ImageC]
/Pattern <</Pat6 200 0 R>>
/ColorSpace <</DefaultRGB [/ICCBased 137 0 R]>>>>
/Annots 197 0 R>>
endobj

201 0 obj
<</Length 202 0 R
/Filter /FlateDecode
/Type /ObjStm
/N 5
/First 37>>
stream
x������ �{?eR�g���*Ҧ��j�T�-0&3h<`�w����D�)[m(|����4bD��U�
I�A;���y��P�pW�[������v]��!��Ѓ�AYG:�[$']/j#R�NSD*���)��%�����]�r���ù��菹->؁����>лS)K�@��d�i�F�$�#u���xK�`��f���k7�6���a�+>�����@��3M:�8\���/�8{kj=�q43�L��P\2�9�^�]o��^.&]���
�?o���`H!��Z2tJ �&}�$�$ߖЇ�eh���!6^�I���e���c03�7�Q&���'S���g&�؄	�⎧�2��_;���@E��k�wQT�=���/#Û��s<濚	�a2���;��K� *�Roc��~���
endstream
endobj

202 0 obj
426
endobj

203 0 obj
<</Length 204 0 R
/Filter /FlateDecode>>
stream
x��Y�n$�}���� K�U�� �h?&�pF�`����)��ͮ���8�##�ټ��:E}���W��~�~����~���N�g��>rQi��Q_I�r��ʅ�I�����/���_��B���e}�ۧm5������˟���׺���Q�1.g�e����;N�CM�Hb��*�t��������_$�X��\9\��v��!��}��\>���7��}����?^b±%30�#1F_F�[{��+���>�8/i?��J�m0$WR�-��ױ��~�G��}�'�ڏ\e<Z��e�����(yG�d?���Qv)��F���7���좤� {z����}lɷ��[�m�K!,H�E����"*ե\���5�-�T���`s��g����ם+�tCٹ���@B�HQx�y�����m��>`��>|N���B�dDt)FcB��Y�D=p�)�d}��b�o.{�#���[G�J���J�G��}@�"�χ�,%���@���#�[�Xֈ}ĲA��~k��~t��:�Fc��ex%�=�|�aW�g����g��X���x����s������iA���b��>l���߰�X�g֯�b�G����jw0������rp���oͧ�p<6��cSH�i�x����x2�$n�iP�X>1�(���Ot,�Z �T�EG+gP�����OY	�ި lMh�gT��W���|�	�S!��_F�+!}`��x�細��[}�\�Ă.��ꪤp�	Ϫ�iӳ^��2=-�r�� `!r��B��$L;�Ӓ�OA��ق�h��/��r"$�w4�<�D���D����RR�d	�"�%�avU��Y�]1�bT���tD�o& e<���=!��60�R-�Wxa���o�J��qZ��F0δ�b�����y��y_:�����)0R3�v�?��A#�^��W�z��z:#��s�'��[J,��Շ��=�Z�gTg��� �A�K��焋�-b��z�GV�Md0���7q�F�K/�+F��P��!A;��Np�Vd���H��j��e2$ �6M��2�a����F��]��n;@C�x0`/{���K�?1�	ed��!=3��CUA�L�v����+E��4��G`��ΫpH�Hr�{(t���Ľ�Z"U���YQ�����8Z��>�W<;�h�:Ok�)��VR!6V+%��X4����;�l9���� ?N@�;MN���~!���~���5_������M$i9Z��f�}D���h���d1rM�G'�s6D�&$E`��L��O�#f��W�_���ꅰFc�ZVw ������ګ�O���im�J>�������@����JW������\lH�4�uk��wU?j	��r�e����ء )��+Fz�:X+[JL]"���v�JUf<��G����2>�x�s��ԛ�����}�N ���j�M+��Ԩ(�(����������jlY�g_j+�E������mŶ�W�Q���1��[R8:6��2x-�,0ǲ�F����� B����tu�W�n�������Vj>���4�	H#�L ��Yk<!ǋ�vs {�Pb�&I�E˺���V��|�o�bYh�ΐY�^�|��wh[	>��y��o�pL�?������Ð��������K}N
Ԁ��&��IkrTK��b{[���j�棢mj����h�H����K�ˇQ��c��̴c�E��c�M�#�Ƴ!�ъ����ׯli���e*�Jو��Јr���`��ɯ�u\�
endstream
endobj

204 0 obj
1786
endobj

9 0 obj
<</Type /Page
/Parent 2 0 R
/MediaBox [0 0 841.8898 595.2756]
/Contents 203 0 R
/Resources <</Font <</F3 144 0 R
/F4 164 0 R>>
/XObject <</I9 208 0 R>>
/ProcSet [/PDF /Text /ImageC]
/ColorSpace <</DefaultRGB [/ICCBased 137 0 R]>>>>
/Annots 207 0 R>>
endobj

209 0 obj
<</Length 210 0 R
/Filter /FlateDecode
/Type /ObjStm
/N 3
/First 21>>
stream
x���=O�0�w��a�w�:�B*S����N��ؑ�(ʿ�iXظ�N�}��G�-0$��K�@l:��Ak��#����28��bF�q6á��(^oA2F�JI�dE�%H.�dJ}���X�bE�O�|�z���~�m�1����+Z<|�<�O���LƜLv�%{ڛtu'7Ĕq�m��&X�ۘ�5c�'�a�S�^�	�[ց��qx|.��Ҳ@\�;�Қl���g�v��7����7�]z^
endstream
endobj

210 0 obj
251
endobj

211 0 obj
<</Length 212 0 R
/Filter /FlateDecode>>
stream
x��Xێ�6}����QD���;}l�@?�mM�䥿�Cɖm�7�f���-����!��'r�x����g�d�����O����?z`�׻�.�� .QM�#�tAeJ�/q=c�Y�w�c:ǔ��u������^��_`�����f��ߝ�~�j��$�`�+���c7D��Gr���S��$��G(â5xyY��x���D��p~���~�g��ˇӓ\X�����/���?��S`�����ēL��$o�ߗ�l�.����k��]���B�$�!��U�˽�)�SH�㗃���V��2���e� ��q�C� ��߷9��] �����!�X��x�p��������@�I<@�5'D�=q�,VW��a�Fw����y}J.lh���i�~�Iy��j}Ist��*�=����R��%Q�Uo���xr�;kʪL�5�dZ+�9�H]J��5!�'����Eb��O���t ��X�ޘ���XC}R����1G��	쑻5�!�E� P�ViԽ�E%C�N��ټ!�Gr��1 x6��WÞ�A�pj���,.R����B�p����CӔ��2��3z`���x�
���,�y�C�p�ֲ�C��Ϫ�ـ�6���uyg�]Wy�����-��c��7���(suEB{�HD9����H��Uk+��Hpa��
�x�O�
�:��_�ܭ�4�HB�+TSخ�<�� ���
_M��J�[J0Cj��qȑr
6]��k
�)��w��M�qE�?��Ќ�*���z7�`�D��e�,�x�7�SF��l19IF<T�dF֤�Vq+.ʙop���F�m�Z�׹��~%�=��.�ȿ	_�E��� M�nK��G�.��W#c������H
�/�u��%k��6��"�57�0`�
��
W*Ц�8`c)��yDUt���(u�Ay\v�I��PE^�D��)}C����M�W��b!nK4��L��/�z��ʧ�l�A*��P�W�����ƼIlx�݉��`Ty��X����� WG421�&F��_��T�9�[´�+g��F�>�V�}-F\��4"�����������.���D6���QJ�Y�(<��&v`iD�����#2��V3�
ָ��r��@'�bJ���:r�5�T�*����J��;5vJ_An���^��z��`�gL�iA�T��zš�@_.�t�o��LKbR"�� O�#�r�[
Client: To Do Android; Version: 2.109.8580.00.betabuild#: 0;UserId: e4d0ed1b31d50fee; SessionId: a54ab79f-7e77-4310-80fa-e179574e41fc; DeviceId: 2e83ca9200153cbb
THANK YOU JESUS CHRIST MY LORD
   JESUS CHRIST IS MY DELIGHTED LORD 💖 